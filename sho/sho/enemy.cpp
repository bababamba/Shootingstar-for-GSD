#include "enemy.h"

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

void enemy::hit() { 
	hp--;
	if( hp < 1 ) { 
		die();
	}
}

void enemy::die() { 
	if( has_item ) { 
		//★아이템 생성
	}
	//★화면 밖으로 치우기, Manager의 bullet 없어지는 거 참조, e_type 또한 nullptr로 바꿔줘야 한다
}

void enemy::set_type(enemy_type* para_type) {
	if( para_type == nullptr ) { 
		e_type = nullptr;
		return;
	}
	for( int i : fire_delay ) {
		i = 5;
	}
	e_type = para_type;
	e_type->init(&e_sdl, &hp);
}