/*
 * character.h
 *
 *  Created on: 08/01/2020
 *      Author: megab
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "map.h"

typedef enum{
	IDLE1,
	IDLE2,
	IDLE3,
	IDLE4,

	WALK1,
	WALK2,
	WALK3,
	WALK4,
	WALK5,

	RWALK1,
	RWALK2,
	RWALK3,
	RWALK4,
	RWALK5,



	STUN,
	BLOCK,

	PUNCH,
	LOWPUNCH,
	HIGHPUNCH,
	FWRDPUNCH,
	FWRDLOWPUNCH,
	FWRDHIGHPUNCH,

	KICK,
	LOWKICK,
	HIGHKICK,
	FWRDKICK,
	FWRDHIGHKICK,
	FWRDLOWKICK,

	CROUCH1,
	CROUCH2,
	CROUCHPUNCH,
	CROUCHKICK,

	JUMP,
	FWRDJUMP,
	JUMPPUNCH,
	JUMPKICK,

	HADOUKEN, //MAYBE?
	SHOULDERTOSS,

	KNOCKDOWN, //BLIVER LIGGNEDE
	RECOVER, //REJSER SIG OP

	HIT,
	FACEHIT,
	CROUCHHIT,

	VICTORY,
	KO

}state;


typedef struct Character{
	//Sprite?
	//BMP* image;
	char sprite;
	//Health
	int HP;
	//BMP* healthbar;

	//Position
	int x;
	int y;

	//Player
	int player;

	//Character state
	state state;

}character;




/*character initPlayer(char* name, int player, int HP, int x){
	character name;
	name.player = player;
	name.HP = HP;
	name.x = x;

	return name;
}*/

/*character* trackCharacter(){

}*/

#endif /* CHARACTER_H_ */
