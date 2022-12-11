#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
struct SDL_Renderer;
static struct charger : public enemy_type {
public:
	charger(SDL_Renderer* M_renderer);
	void move(enemy* enem);
	void render(SDL_Rectf&);
	void type_test() {
		cout << "it's charger\n";
	}
};