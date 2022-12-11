#pragma once
#include "SDL_Rectf.h"

class Bullet {
private:
	float collision_x;
	float collision_y;
	float collision_w;
	float collision_h;
	SDL_Texture* texture;

public:
	SDL_Rectf b_sdl;

	void init(float x, float y, float w, float h);
	void move();
	void render();
	void SetTexture(SDL_Texture*);
	SDL_Rectf getCollisonRectf();
};