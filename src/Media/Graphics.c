/*
 * GDI.c
 *
 *  Created on: 6. jan. 2020
 *      Author: Kris
 */

#include "Graphics.h"


#define DYNCLK_BASEADDR XPAR_AXI_DYNCLK_0_BASEADDR
#define VGA_VDMA_ID XPAR_AXIVDMA_0_DEVICE_ID
#define DISP_VTC_ID XPAR_VTC_0_DEVICE_ID //Hvad er VTC?

#define FRAMEBUF_MAX_VALUES (SCREEN_WIDTH * SCREEN_HEIGHT * 4) //4 bytes pr. pixel
#define STRIDE (SCREEN_WIDTH * 4) //Hvor mange værdier per horizontale linje
#define pixelAddrSize SCREEN_WIDTH * SCREEN_HEIGHT * 4


DisplayCtrl dispCtrl;
XAxiVdma vdma;
u8 readyBuffer, curBuffer = 0;
u8  frameBuf[DISPLAY_NUM_FRAMES][FRAMEBUF_MAX_VALUES] __attribute__((aligned(0x20)));
u8 *pFrames[DISPLAY_NUM_FRAMES]; //array of pointers to the frame buffers
u8 *background;
u8 *screen;

void GDI_init() {
	XAxiVdma_Config *vdmaConfig;
	int Status;
	int i;

	for (i = 0; i < DISPLAY_NUM_FRAMES; i++)
	{
		pFrames[i] = frameBuf[i];
	}

	//Init VDMA
	vdmaConfig = XAxiVdma_LookupConfig(VGA_VDMA_ID);
	if (!vdmaConfig)
	{
		xil_printf("No video DMA found for ID %d\r\n", VGA_VDMA_ID);
		return;
	}
	Status = XAxiVdma_CfgInitialize(&vdma, vdmaConfig, vdmaConfig->BaseAddress);
	if (Status != XST_SUCCESS)
	{
		xil_printf("VDMA Configuration Initialization failed %d\r\n", Status);
		return;
	}

	//Init display
	Status = DisplayInitialize(&dispCtrl, &vdma, DISP_VTC_ID, DYNCLK_BASEADDR, pFrames, STRIDE);
	if (Status != XST_SUCCESS) {
		xil_printf("Display Ctrl initialization failed during demo initialization%d\r\n", Status);
		return;
	}
	Status = DisplayStart(&dispCtrl);
	if (Status != XST_SUCCESS) {
		xil_printf("Couldn't start display during demo initialization%d\r\n", Status);
		return;
	}

	//Set video resolution
	DisplayStop(&dispCtrl);
	switch(SCREEN_HEIGHT) {
	case 1080:
		DisplaySetMode(&dispCtrl, &VMODE_1920x1080);
		break;
	case 720:
		DisplaySetMode(&dispCtrl, &VMODE_1280x720);
		break;
	default:
		DisplaySetMode(&dispCtrl, &VMODE_640x480);
	}
	DisplayStart(&dispCtrl);
}

void setMemSettings() {

	Xil_SetTlbAttributes(pFrames[0], 0x15de6);
	Xil_SetTlbAttributes(pFrames[1], 0x15de6);
	Xil_SetTlbAttributes(pFrames[2], 0x15de6);

}
void clearScreen() {
	memcpy(pFrames[curBuffer], background, pixelAddrSize);
}

void initBackground(char* path) {
	free(background);
	free(screen);
	background = malloc(pixelAddrSize);
	screen = malloc(pixelAddrSize);
	bitmap * BCKGR = readBitmapFromSD(path);
	drawImage(BCKGR, 0, 0, 0);
	memcpy(background, screen, pixelAddrSize);
	//Bagvendt fordi vi er ligeglade med tiden når vi initialiserer
	//Så slipper vi for et ekstra argument til drawImage
}

void flushBuffer() {
	//Xil_DCacheFlushRange((unsigned int) pFrames[curBuffer], 1920*1080*4);
	readyBuffer = curBuffer;
	curBuffer++;
	if (curBuffer >= DISPLAY_NUM_FRAMES)
		curBuffer = 0;
}

void changeFrameBuffer() {
		DisplayChangeFrame(&dispCtrl, readyBuffer);
}

int drawImage(bitmap * inputBitmap, u32 x, u32 y, u8 alpha) {
    u32 iPixelAddr = (x + y * SCREEN_WIDTH) * 4;
	u32 i, j, heightOffset = 0;
	u32 widthCond = (inputBitmap->width) << 2; //Condition outside loop for a little more speed

    for (i = 0; i < inputBitmap->height; i++) {
    	for (j = 0; j < widthCond; j+=4) {
    		if ((alpha == 0) || (*(inputBitmap->data + j + 4 + heightOffset) != 0)) { //Hvis alpha ikke er 0
    			screen[iPixelAddr]     = *(inputBitmap->data + j     + heightOffset); //Blue
    			screen[iPixelAddr + 1] = *(inputBitmap->data + j + 1 + heightOffset); //Green
    			screen[iPixelAddr + 2] = *(inputBitmap->data + j + 2 + heightOffset); //Red
    		}
    		iPixelAddr += 4;
    	}

    	if (inputBitmap->width < SCREEN_WIDTH) {
    		iPixelAddr += (SCREEN_WIDTH - inputBitmap->width) << 2;
    	}
    	if (iPixelAddr > FRAMEBUF_MAX_VALUES - 3)
    		break;

    	heightOffset += inputBitmap->stride;
    }

    Xil_DCacheFlushRange((unsigned int) screen, 1920*1080*4);
    return 0;
}

void drawAlphaMappedImage(bitmap * image, u32 x, u32 y) {
	u32 iPixelAddr = (x + y * SCREEN_WIDTH) * 4;
	int line, j;
	u8 * dataPointer = image->data;
	u8 * screenPointer = pFrames[curBuffer];

	for (line = 0; line < image->height; line++) {
		for (j = 0; j < image->alpha->line[line]->alphaCount; j++) {
			//Hvis vi overskrider array crasher vi ikke...
			if (iPixelAddr + (image->alpha->line[line]->pixelStart[j] << 2) + (image->alpha->line[line]->pixelCount[j] << 2 ) > FRAMEBUF_MAX_VALUES - 4) {
			    break;
			}
			memcpy(screenPointer + iPixelAddr + (image->alpha->line[line]->pixelStart[j] << 2) // + (image->alpha->line[line]->pixelStart[j]* 4)
				   ,dataPointer + (image->alpha->line[line]->pixelStart[j] << 2)
				   ,image->alpha->line[line]->pixelCount[j] << 2
				   );
		}
		iPixelAddr += SCREEN_WIDTH << 2;


		dataPointer += image->stride;
	}
}

void drawReverseAlphaMappedImage(bitmap * image, u32 x, u32 y) {
	u32 iPixelAddr = (x + y * SCREEN_WIDTH) * 4;
	int line, j;
	u8 * dataPointer = image->data;
	u8 * screenPointer = pFrames[curBuffer];

	for (line = 0; line < image->height; line++) {
		for (j = 0; j < image->alpha->line[line]->alphaCount; j++) {
			//Hvis vi overskrider array crasher vi ikke...
			if (iPixelAddr + (image->alpha->line[line]->pixelStart[j] << 2) + (image->alpha->line[line]->pixelCount[j] << 2 ) > FRAMEBUF_MAX_VALUES - 4) {
			    break;
			}
			memcpy(screenPointer + iPixelAddr + (image->alpha->line[line]->pixelStart[j] << 2) // + (image->alpha->line[line]->pixelStart[j]* 4)
				   ,dataPointer + (image->alpha->line[line]->pixelStart[j] << 2)
				   ,image->alpha->line[line]->pixelCount[j] << 2
				   );
		}
		iPixelAddr += SCREEN_WIDTH << 2;


		dataPointer += image->stride;
	}
}
