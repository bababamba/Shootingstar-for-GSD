#pragma once
#include "SDL_Rectf.h"
#include "enemy_type.h"
#include "Manager.h"

#include <iostream>
using namespace std;

static struct zigzag : public enemy_type {
public:
	zigzag(SDL_Renderer* M_renderer);
	void move(enemy* enem);
	void how_to_fire(enemy* enem);

	void type_test() {
		cout << "it's zigzag\n";
	}
};