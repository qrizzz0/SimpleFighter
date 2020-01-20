/*
 * controls.h
 *
 *  Created on: 08/01/2020
 *      Author: megab
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "character.h"

int exists(char inputCmd);
void execCmd(character* character1, character* character2, char inputCmd);
void processCmd(character* character1, character* character2, char inputCmd);
int hit(character* character1, character* character2);





#endif /* CONTROLS_H_ */
