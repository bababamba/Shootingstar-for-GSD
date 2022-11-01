#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
class SDL_Renderer;
static struct basic : public enemy_type {
public:
	basic(SDL_Renderer* M_renderer);
	void how_to_fire(enemy* enem);

	void type_test() {
		cout << "it's basic\n";
	}
};