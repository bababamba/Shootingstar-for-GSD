#include "SDL_Rectf.h"
#include "enemy_type.h"
#include "Manager.h"
#pragma once

#include <iostream>
using namespace std;

static struct basic : public enemy_type {
public:
	basic() { 
		wh[0] = 64;
		wh[1] = 64;
		max_hp = 1;
		speed = 4;
	}
	void how_to_fire( SDL_Rectf e_sdl, int(&i)[4]) {
		if( i[0] <= 0 ) {
			Manager::get_m()->bullet_set(e_sdl.x, e_sdl.y, 0, 1, false);
			i[0] = 30;
		}
	}
	void type_test() {
		cout << "it's basic\n";
	}
};