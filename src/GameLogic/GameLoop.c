#include <stdio.h>
#include "xil_printf.h"
#include "xil_types.h"
#include "xparameters.h"

#include "../Media/Graphics.h"
#include "../Media/SDCard.h"
#include "../Interrupts/interrupt_variables.h"
#include "../Interrupts/handlers.h"
#include "../Interrupts/intr_common.h"
#include "animation.h"
#include "character.h"

//XVtc_Config *VtcCfgPtr;

int main() {
	GDI_init();
	initSDCard();
	bitmap * BGR = readBitmapFromSD("Sprite.bgr");

	bitmap * walk[5];
	walk[0] = readBitmapFromSD("Ryu/walk1.bgr");
	walk[1] = readBitmapFromSD("Ryu/walk2.bgr");
	walk[2] = readBitmapFromSD("Ryu/walk3.bgr");
	walk[3] = readBitmapFromSD("Ryu/walk4.bgr");
	walk[4] = readBitmapFromSD("Ryu/walk5.bgr");

	bitmap * rwalk[5];
	rwalk[0] = readBitmapFromSD("Ryu/rwalk1.bgr");
	rwalk[1] = readBitmapFromSD("Ryu/rwalk2.bgr");
	rwalk[2] = readBitmapFromSD("Ryu/rwalk3.bgr");
	rwalk[3] = readBitmapFromSD("Ryu/rwalk4.bgr");
	rwalk[4] = readBitmapFromSD("Ryu/rwalk5.bgr");

	bitmap * idle[4];
	idle[0] = readBitmapFromSD("Ryu/idle1.bgr");
	idle[1] = readBitmapFromSD("Ryu/idle2.bgr");
	idle[2] = readBitmapFromSD("Ryu/idle3.bgr");
	idle[3] = readBitmapFromSD("Ryu/idle4.bgr");

	bitmap * crouch[2];
	crouch[0] = readBitmapFromSD("Ryu/crou1.bgr");
	crouch[1] = readBitmapFromSD("Ryu/crou2.bgr");

	//Init player

	character *character1, p1ptr;
	character1 = &p1ptr;

	character1->player = 1;
	character1->x = 10;
	character1->y = 100;
	character1->HP = 3;
	//player1.sprite = 'o';
	character1->state = WALK1;

	//timer
	u32 oldCount = counter;

	//Enable vsync interrupt
	PictureReady = 0;
	initializeInterrupts();

	int y = 100;
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

	initBackground("BG/stfbg1.bgr");

	clearScreen();
	flushBuffer();
	setMemSettings();
	while (1) {
		if (PictureReady == 0) {

			clearScreen();
			//drawReverseAlphaMappedImage(BGR, x, y);
			//drawAlphaMappedImage(walk[0], x, y);
			/*drawAlphaMappedImage(BGR, x3, y3);
			 drawAlphaMappedImage(BGR, x4, y4);
			 drawAlphaMappedImage(BGR, x5, y4);
			 drawAlphaMappedImage(BGR, x6, y2);
			 */

			/*if (counter % 10 == 0 && animationcnt <= 4) {
			 animationcnt++;
			 }else if (animationcnt > 4){
			 animationcnt = 0;
			 }

			 if (animationcnt == 0) {
			 drawAlphaMappedImage(walk[0], x, y);
			 }
			 if (animationcnt == 1) {
			 drawAlphaMappedImage(walk[1], x, y);
			 }
			 if (animationcnt == 2) {
			 drawAlphaMappedImage(walk[2], x, y);
			 }
			 if (animationcnt == 3) {
			 drawAlphaMappedImage(walk[3], x, y);
			 }
			 if (animationcnt == 4) {
			 drawAlphaMappedImage(walk[4], x, y);
			 }*/

			//Walk(walk, x, y, 30);
			switch (character1->state) {
			case IDLE1:
				drawAlphaMappedImage(idle[0], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = IDLE2;
					oldCount = counter;
				}
				break;
			case IDLE2:
				drawAlphaMappedImage(idle[1], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = IDLE3;
					oldCount = counter;
				}
				break;
			case IDLE3:
				drawAlphaMappedImage(idle[2], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = IDLE4;
					oldCount = counter;
				}
				break;
			case IDLE4:
				drawAlphaMappedImage(idle[3], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = WALK1;
					oldCount = counter;
				}
				break;
			case WALK1:
				character1->x += 1;
				drawAlphaMappedImage(walk[0], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = WALK2;
					oldCount = counter;
				}
				break;
			case WALK2:
				character1->x += 1;
				drawAlphaMappedImage(walk[1], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = WALK3;
					oldCount = counter;
				}
				break;
			case WALK3:
				character1->x += 1;
				drawAlphaMappedImage(walk[2], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = WALK4;
					oldCount = counter;
				}
				break;
			case WALK4:
				character1->x += 1;
				drawAlphaMappedImage(walk[3], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = WALK5;
					oldCount = counter;
				}
				break;
			case WALK5:
				character1->x += 1;
				drawAlphaMappedImage(walk[4], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = IDLE1;
					oldCount = counter;
				}
				break;

			case RWALK1:
				drawAlphaMappedImage(rwalk[0], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = RWALK2;
					oldCount = counter;
				}
				break;
			case RWALK2:
				drawAlphaMappedImage(rwalk[1], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = RWALK3;
					oldCount = counter;
				}
				break;
			case RWALK3:
				drawAlphaMappedImage(rwalk[2], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = RWALK4;
					oldCount = counter;
				}
				break;
			case RWALK4:
				drawAlphaMappedImage(rwalk[3], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = RWALK5;
					oldCount = counter;
				}
				break;
			case RWALK5:
				drawAlphaMappedImage(walk[4], character1->x, character1->y);
				if (oldCount + 15 <= counter) {
					character1->state = IDLE1;
					oldCount = counter;
				}
				break;
			}

			//drawAlphaMappedImage(walk[0], character1->x, character1->y);

			//character1->y += 0;
			//character1->x += 1;
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
