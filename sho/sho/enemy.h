#include "SDL_Rectf.h"
#include "basic_enemy.h"
#pragma once

class enemy {
private:
	int hp;
	int fire_delay[4];	//���� ������, ������ ������ 2~4�� ������ ���� ����� �����Ƿ� �迭�̴�

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