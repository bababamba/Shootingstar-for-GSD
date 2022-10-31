#pragma once
#include "Manager.h"
#include "SDL_Rectf.h"

class player {
public:
	SDL_Rectf p_sdl;
	
	player();
	void init();
	void attack();
	void set_attack_level(const int i);
	void die();
private:
	int attack_level;
};