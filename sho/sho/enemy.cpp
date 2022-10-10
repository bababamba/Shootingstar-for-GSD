#include "enemy.h"

void enemy::fire() { 
	for( int i = 0; i < 4; i++ ) {
		if( --fire_delay[i] < -10 )
			break;
	}
	e_type->how_to_fire(e_sdl, fire_delay);
}

void enemy::move() { 
	e_type->move(e_sdl);
}

void enemy::set_type(enemy_type* para_type) {
	for( int i : fire_delay ) {
		i = 5;
	}
	e_type = para_type;
	e_type->init(&e_sdl, &hp);
}