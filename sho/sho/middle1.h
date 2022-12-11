#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
//class SDL_Renderer;

static struct middle1 : public enemy_type {
public:
	middle1(SDL_Renderer* M_renderer);
	void move(enemy* enem);
	void how_to_fire(enemy* enem);
	void render(SDL_Rectf&);
	void type_test() {
		cout << "it's middle1\n";
	}
};