/*
 * SDCard.c
 *
 *  Created on: 7. jan. 2020
 *      Author: Kris
 */

#include "SDCard.h"

FATFS FatFs;

bitmap * readBitmapFromSD(char* path) {
	FIL fp;
	int status;

	//Open file
	status = f_open(&fp, path, FA_READ | FA_OPEN_EXISTING);
	if (status != FR_OK) {
		xil_printf("ERROR: Could not open file!\n\r");
		return 1;
	}

	/* Pointer to beginning of file .	 */
	/*status = f_lseek(fp, 0);
	if (status) {
		xil_printf("SD f_lseek failed \r\n");
		return 2;
	} */ //Vi skal lige finde ud af hvorfor dette er relevant...

	bitmap * file = (bitmap *) malloc(sizeof(bitmap));
    if(file == NULL){
    	xil_printf("ERROR: not enough space available\r\n");
        return 1;
    }

    //Set file properties
    file->size = f_size(&fp);

    //Allocate space for file in heap
    u8 * fileData = malloc(file->size);
    if(fileData == NULL){
    	xil_printf("ERROR: not enough space available for file in heap\r\n");
        return 1;
    }

    //read data
    UINT bytesRead;
    status = f_read(&fp, (void *)fileData, file->size, &bytesRead);
    if (status != FR_OK){
    	xil_printf("ERROR: Couldn't read data from file pointer %d\r\n", status);
    	return 4;
    }

    //Get width and height from file header
    file->height = *(fileData) | (*(fileData + 1)) << 8;
    file->width = *(fileData + 2) | (*(fileData + 3)) << 8;
    file->stride = file->width * 4;
    file->pixels = file->width * file->height;
    //Jump pointer 4 bytes to image data
    fileData += 4;

    xil_printf("\n width: %d, height: %d \r\n", file->width, file->height);

    file->data = fileData;

    int i, j;
    //for (i = 0; i < file->height - 1; i++) {
    //	for (j = 0; j < file->stride; j++)
    //		file->strideReversedData[file->stride-1-j] = file->data[j];
    //}
    //file->strideReversedData;


    xil_printf("Calculating alpha! \r\n");
    calculateAlpha(file);
    xil_printf("First line alpha pixelstart: %d count: %d alphacount: %d\r\n", file->alpha->line[55]->pixelStart[0], file->alpha->line[55]->pixelCount[0], file->alpha->line[55]->alphaCount);
    xil_printf("Pixel start 2: %d, Pixel count 2: %d", file->alpha->line[55]->pixelStart[1], file->alpha->line[55]->pixelCount[1]);

    f_close(&fp);

	return file;
}

int freeBitmapData(bitmap * input) {
	if (input) {
		free(input->alpha->line);
		free(input->alpha);
		free(input->data);
		free(input);
		return 0;
	}
	return 1;
}

void initSDCard() {
	int status;
	status = f_mount(&FatFs, "", 0);
	if (status != FR_OK) {
		xil_printf("Something is wrong while mounting SD-Card! Status: %d\n", status);
	}
}

void calculateAlpha(bitmap * input) {
	input->alpha = malloc(sizeof(alphaMap));
	input->alpha->lineCount = input->height;

	int i, j, a;
	u8 pixelCount = 0;
	u8 lineAlphas = 0;

	input->alpha->line = malloc(sizeof(u16) * input->size); //Lav plads til pointers
	for (i = 0; i < input->height; i++) {
		input->alpha->line[i] = malloc(sizeof(lineAlpha));
		for (j = 3; j < input->stride; j+=4) {
			if (*(input->data + j + (i * input->stride)) != 0) {
				if (pixelCount == 0) {
					if (j == 3) { a = 0; } else { a = j / 4; } //Udregn pixel fra arrayplads
					input->alpha->line[i]->pixelStart[lineAlphas] = a;
				}
				pixelCount++;
			} else if (pixelCount > 0 && *(input->data + j) == 0) {
				//*((*(input->alpha->line + i))->pixelCount + lineAlphas) = pixelCount;
				input->alpha->line[i]->pixelCount[lineAlphas] = pixelCount;
				pixelCount = 0;
				lineAlphas++;
			}
		}

		if (pixelCount != 0) {
			//*((*(input->alpha->line + i))->pixelCount + lineAlphas) = pixelCount;
			input->alpha->line[i]->pixelCount[lineAlphas] = pixelCount;
			lineAlphas++;
		}
		(*(input->alpha->line + i))->alphaCount = lineAlphas;
		if (lineAlphas == 0)
			input->alpha->line[i]->pixelCount[0] = 0;

		lineAlphas = 0;
		pixelCount = 0;
	}
}
