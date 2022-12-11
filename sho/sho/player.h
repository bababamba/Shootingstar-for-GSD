#pragma once
#include "Manager.h"
#include "SDL_Rectf.h"

class player {
public:
	SDL_Rectf p_sdl;
	
	player();
	void init();
	void attack();
	void attack_delay_decrease();
	void increse_attack_level(const int i);
	void die();
	void render();
	void SetTexture(SDL_Texture*);
	SDL_Rectf getCollisonRectf();
private:
	int attack_level;
	float attack_delay;	
	SDL_Texture* texture;

};