/*
 * controls.c
 *
 *  Created on: 08/01/2020
 *      Author: megab
 */
#include "controls.h"

//#define CMD_AMOUNT 10


/*character* trackPlayer(){


 }*/

int hit(character* character1, character* character2) {
	int success = 0;
	if (map[character1->x + 1] == 'o' || map[character1->x - 1] == 'o') {
		success++;
		character2->HP -= 1;
		character2->state = STUN;
	}
	return success;
}

int kick(character* character1, character* character2) {
	int success = 0;
	if (map[character1->x + 1] == 'o' || map[character1->x - 1] == 'o') {
		success++;
		character2->HP -= 2;
		character2->state = STUN;
	}
	return success;
}
/*
int exists(char inputCmd) {
	int i, bool = 0;

	for (i = 0; i < CMD_AMOUNT; i++) {
		if (inputCmd == cmd[i]) {
			bool = 1;
			break;
		}
	}
	return bool;
}*/

void execCmd(character* character1, character* character2, char inputCmd) {

	switch (inputCmd) {
	case 'a':
		printf("Moving to the left\n");
		map[character1->x] = '_';
		character1->x -= 1;
		map[character1->x] = 'o';


		break;
	case 'd':
		printf("Moving to the right\n");
		map[character1->x] = '_';
		character1->x += 1;
		map[character1->x] = 'o';
		break;
	case 'w':
		printf("Jumping\n");
		character1->sprite = '¤';
		map[character1->x] = character1->sprite;
		character1->y += 2;
		break;
	case 's':
		printf("Crouching\n");
		character1->sprite = '.';
		map[character1->x] = character1->sprite;
		//player->imgptr = bitmap * crouch
		character1->y -= 2;
		break;
	case ' ':
		printf("Hitting: ");
		if (hit(character1, character2) == 1) {
			printf("success!\n");
			character2->state = STUN;
			printf("Character%d state = %d\n", character2->player, character2->state);
		} else {
			printf("miss\n");
		}
		if (character2->HP <= 0) {
			printf("Player %d has lost\n", character2->player);
		} else {
			printf("Player %d has been damaged, %d HP left\n",
					character2->player, character2->HP);
		}
		break;
	case 'k':
		//Tænk på at lave kick funktion med mere skade og recover time
		printf("Kicking: ");
		if (hit(character1, character2) == 1) {
			printf("success!\n");
		} else {
			printf("miss\n");
		}
		if (character2->HP <= 0) {
			printf("Player %d has lost\n", character2->player);
		} else {
			printf("Player %d has been damaged, %d HP left\n",
					character2->player, character2->HP);
		}
		break;
	case 'b':
		printf("Blocking\n");
		character1->state = BLOCK;
		printf("Character%d state = %d\n", character1->player, character1->state);
		break;
	default:
		break;
	}
}

void processCmd(character* character1, character* character2, char inputCmd) {
	/*if (exists(inputCmd) == 1) {
	 execCmd(character1, character2, inputCmd);
	 } else {
	 //Do nothing
	 }*/

	execCmd(character1, character2, inputCmd);
}
