#include "SDL_Rectf.h"
#include "basic_enemy.h"
#pragma once

class enemy {
private:
	int hp;
	int fire_delay[4];	//공격 딜레이, 강력한 적들은 2~4개 정도의 공격 방식을 가지므로 배열이다

	enemy_type* e_type;
public:
	SDL_Rectf e_sdl;
	//enemy();


	void fire();
	void move();
	void set_type(enemy_type* para_type);
	void test() { 
		e_type->type_test(); 
	}
};