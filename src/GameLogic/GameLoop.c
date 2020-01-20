#include <stdio.h>
#include "xil_printf.h"
#include "xil_types.h"
#include "xparameters.h"

#include "../Media/Graphics.h"
#include "../Media/SDCard.h"
#include "../Interrupts/interrupt_variables.h"
#include "../Interrupts/handlers.h"
#include "../Interrupts/intr_common.h"

//XVtc_Config *VtcCfgPtr;


int main() {
	GDI_init();
	initSDCard();
	bitmap * BGR = readBitmapFromSD("Pinkie.bgr");

	//Enable vsync interrupt
	PictureReady = 0;
	initializeInterrupts();

	int y = 0;
	int x = 0;
	int y2 = 700;
	int x2 = 700;
	int y3 = 400;
	int x3 = 50;
	int x4 = 800;
	int y4 = 40;
	int x5 = 300;
	int x6 = 600;
	int nextframe = 0;

	initBackground("BCKGR1.bgr");

	clearScreen();
	flushBuffer();
	setMemSettings();
	while (1) {
			if (PictureReady == 0) {

				clearScreen();
				drawReverseAlphaMappedImage(BGR, x, y);
				drawAlphaMappedImage(BGR, x2, y2);
				drawAlphaMappedImage(BGR, x3, y3);
				drawAlphaMappedImage(BGR, x4, y4);
				drawAlphaMappedImage(BGR, x5, y4);
				drawAlphaMappedImage(BGR, x6, y2);

				y += 1;
				x += 1;
				x2 += 3;
				y2 += 3;
				x3 += 2;
				y3 += 2;
				y4 += 5;
				x4 += 5;
				x6 += 2;
				x5 += 7;

				nextframe++;

				if (x > SCREEN_WIDTH)
					x = 0;
				if (y > SCREEN_HEIGHT)
					y = 0;
				if (x2 > SCREEN_WIDTH)
					x2 = 0;
				if (y2 > SCREEN_HEIGHT)
					y2 = 0;
				if (x3 > SCREEN_WIDTH)
					x3 = 0;
				if (y3 > SCREEN_HEIGHT)
					y3 = 0;
				if (x4 > SCREEN_WIDTH)
					x4 = 0;
				if (y4 > SCREEN_HEIGHT)
					y4 = 0;
				if (x5 > SCREEN_WIDTH)
					x5 = 0;
				if (x6 > SCREEN_WIDTH)
					x6 = 0;

				flushBuffer();
				PictureReady = 1;
			}
	}

	free(BGR);

	return 0;
}
