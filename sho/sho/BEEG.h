#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
struct SDL_Renderer;

static struct BEEG : public enemy_type {
public:
	BEEG(SDL_Renderer* M_renderer);
	void move(enemy* enem);
	void how_to_fire(enemy* enem);
	void render(SDL_Rectf&);

	void type_test() {
		cout << "it's BIIIIG BEEEEEG\n";
	}
};