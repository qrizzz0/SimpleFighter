/*
 * SDCard.h
 *
 *  Created on: 7. jan. 2020
 *      Author: Kris
 */

#ifndef SRC_SDCARD_H_
#define SRC_SDCARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ff.h"
#include "xsdps.h"

typedef struct {
	u8 alphaCount;
	u8 pixelStart[10];
	u8 pixelCount[10];
} lineAlpha;

typedef struct {
	u8 lineCount;
	lineAlpha ** line;
} alphaMap;

typedef struct {
    u64 size;
    u64 pixels;
    u16 width;
	u16 height;
	u32 stride;
	u8 * data;
	u8 * strideReversedData;
	alphaMap * alpha;
} bitmap;


bitmap * readBitmapFromSD(char* path);
int freeBitmapData(bitmap * input);
void initSDCard();
void calculateAlpha(bitmap * input);

#endif /* SRC_SDCARD_H_ */
