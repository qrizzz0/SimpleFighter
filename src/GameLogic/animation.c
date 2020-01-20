/*
 * animation.c
 *
 *  Created on: 20. jan. 2020
 *      Author: megab
 */

#include "../Media/Graphics.h"
#include "character.h"
/*
void Animate(bitmap * anim[], character* character1, int speed, int cnt) {
	/*if (frame % 1 == 0) {
	 frame = 1;
	 }
	 if (frame % 2 == 0) {
	 frame = 2;
	 }
	 if (frame % 3 == 0) {
	 frame = 3;
	 }
	 if (frame % 4 == 0) {
	 frame = 4;
	 }

	u32 oldCount;

	switch (character1->state) {
	case IDLE1:
		drawAlphaMappedImage(anim[0], character1->x, character1->y);
		oldCount = counter;
		if (oldCount + 3 >= counter) {
			character1->state = IDLE2;
		}
	case IDLE2:
		drawAlphaMappedImage(anim[0], character1->x, character1->y);
		oldCount = counter;
		if (oldCount + 3 >= counter) {
			character1->state = IDLE3;
		}
	case IDLE3:
		drawAlphaMappedImage(anim[0], character1->x, character1->y);
		oldCount = counter;
		if (oldCount + 3 >= counter) {
			character1->state = IDLE4;
		}
	case IDLE4:
		drawAlphaMappedImage(anim[0], character1->x, character1->y);
		oldCount = counter;
		if (oldCount + 3 >= counter) {
			character1->state = IDLE1;
		}
	case WALK1:
		drawAlphaMappedImage(anim[0], character1->x, character1->y);
		oldCount = counter;
		if (oldCount + 3 >= counter) {
			character1->state = WALK2;
		}

	case WALK2:
		drawAlphaMappedImage(anim[1], character1->x, character1->y);
		if (cnt % speed == 0) {
			frame++;
		}
		if (oldCount + 3 >= counter) {
			character1->state = WALK3;
		}

	case WALK3:
		drawAlphaMappedImage(anim[2], character1->x, character1->y);
		if (cnt % speed == 0) {
			frame++;
		}
		if (oldCount + 3 >= counter) {
			character1->state = WALK4;
		}
	case WALK4:
		drawAlphaMappedImage(anim[3], character1->x, character1->y);
		if (cnt % speed == 0) {
			frame++;
		}
		if (oldCount + 3 >= counter) {
			character1->state = WALK5;
		}
	case WALK5:
		drawAlphaMappedImage(anim[3], character1->x, character1->y);
		if (cnt % speed == 0) {
			frame++;
		}
		if (oldCount + 3 >= counter) {
			character1->state = IDLE1;
		}
	}

	int animationcnt = 0;

	 //drawAlphaMappedImage(walk[0], x, y);

	 while(animationcnt < 5){

	 if (counter % speed == 0 && animationcnt <= 4) {
	 animationcnt++;
	 }
	 //}else if (animationcnt > 4){
	 //animationcnt = 0;
	 //}

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
	 }
	 }

}*/
