#include "enemy.h"
#include "Manager.h"

void enemy::fire() { 
	for( int i = 0; i < 4; i++ ) {
		if( fire_delay[i]-- < -10 )
			break;
	}
	e_type->how_to_fire(this);
}

void enemy::move() { 
	e_type->move(this);
}

bool enemy::hit() { 
	hp--;
	if( hp < 1 ) { 
		die();
		return true;
	} else { 
		return false;
	}
}

void enemy::die() { 
	e_type = nullptr;
	if( has_item ) { 
		Manager::get_m()->item_set(e_sdl.x, e_sdl.y);
	}
}

void enemy::set_type(enemy_type* para_type) {
	for( int i = 0; i < 4;i++ ) {
		fire_delay[i] = 5;
	}
	SA_var1 = -1;
	SA_var2 = -1;
	SA_bool = false;
	e_sdl.set_speed(0);
	if( para_type == nullptr ) {
		e_type = nullptr;
		return;
	}
	e_type = para_type;
	e_type->init(&e_sdl, &hp);
}