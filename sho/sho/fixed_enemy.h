#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
struct SDL_Renderer;
static struct Fixed : public enemy_type {
public:
	Fixed(SDL_Renderer* M_renderer);
	void how_to_fire(enemy* enem);
	void render(SDL_Rectf& sdl);
	void type_test() {
		cout << "it's basic\n";
	}
};