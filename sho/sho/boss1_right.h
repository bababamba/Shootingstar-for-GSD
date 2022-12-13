#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
struct SDL_Renderer;
static struct boss1_right : public enemy_type {
private:
	SDL_Texture* crash_texture;
	bool crash;
	SDL_Rectf plr;
public:
	boss1_right(SDL_Renderer* M_renderer);
	void how_to_fire(enemy* enem);
	void move(enemy* enem);
	void render(SDL_Rectf& sdl);
	void type_test() {
		cout << "it's boss1_right\n";
	}
	void SetCrash(bool);
};