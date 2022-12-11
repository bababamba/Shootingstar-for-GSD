#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
struct SDL_Renderer;
static struct zigzag : public enemy_type {
public:
	zigzag(SDL_Renderer* M_renderer);
	void move(enemy* enem);
	void how_to_fire(enemy* enem);
	void render(SDL_Rectf&);
	void type_test() {
		cout << "it's zigzag\n";
	}
};