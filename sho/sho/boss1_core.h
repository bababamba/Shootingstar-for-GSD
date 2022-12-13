#pragma once
#include "enemy_type.h"

#include <iostream>
using namespace std;

class enemy;
struct SDL_Renderer;
static struct boss1_core : public enemy_type {
private:
	SDL_Texture* close_texture;
	bool open;
	SDL_Rectf plr;
public:
	boss1_core(SDL_Renderer* M_renderer);
	void how_to_fire(enemy* enem);
	void move(enemy* enem);
	void render(SDL_Rectf& sdl);
	void type_test() {
		cout << "it's boss1_core\n";
	}
	void SetOpen(bool);
};