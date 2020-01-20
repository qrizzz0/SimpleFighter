/*
 * GDI.h
 *
 *  Created on: 6. jan. 2020
 *      Author: Kris
 */

#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_

#include <stdio.h>
#include "xil_printf.h"
#include "display_ctrl/display_ctrl.h"
#include "SDCard.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720



void GDI_init();
void clearScreen();
void flushBuffer();
int drawImage(bitmap * inputBitmap, u32 x, u32 y, u8 alpha);
void initBackground(char* path);
void changeFrameBuffer();
void drawAlphaMappedImage(bitmap * image, u32 x, u32 y);



#endif /* SRC_GRAPHICS_H_ */
