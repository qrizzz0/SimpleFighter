/*
 * controls.c
 *
 *  Created on: 08/01/2020
 *      Author: megab
 */

#include "map.h"


void setMap(int p1, int p2) {
	int i;
	for (i = 0; i < sizeof(map); i++) {
		map[i] = '_';
		if (i == p1 || i == p2) {
			map[i] = 'o';
		}
	}
}

void printMap() {
	int i;
	for (i = 0; i < sizeof(map); i++) {
		printf("%c", map[i]);

	}
}
