#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
struct SDL_Renderer;
static struct boss1_base : public enemy_type {
public:
	boss1_base(SDL_Renderer* M_renderer);
	void move(enemy* enem);
	void render(SDL_Rectf& sdl);
	void type_test() {
		cout << "it's boss1_base\n";
	}
};