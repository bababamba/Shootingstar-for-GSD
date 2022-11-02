#pragma once
#include "SDL_Rectf.h"
#include "enemy_type.h"
#include "Manager.h"
#include "basic_enemy.h"
#include "enemy.h"

basic::basic(SDL_Renderer* M_renderer) {
	wh[0] = 64;
	wh[1] = 64;
	max_hp = 1;
	speed = 4;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/enemy_basic.png"));
}

void basic::how_to_fire(enemy* enem) {
	if( enem->get_fire_delay()[0] <= 0 ) {

		Manager::get_m()->bullet_set(enem->e_sdl.x + wh[0] / 2, enem->e_sdl.y + wh[1] / 2, 0, 1, 8, false);
		enem->get_fire_delay()[0] = 60;
	}
}