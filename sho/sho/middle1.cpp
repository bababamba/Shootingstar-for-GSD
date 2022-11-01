#pragma once
#include "SDL_Rectf.h"
#include "enemy_type.h"
#include "Manager.h"
#include "middle1.h"
#include "enemy.h"
#include <math.h>
#include "player.h"

middle1::middle1(SDL_Renderer* M_renderer) {
	wh[0] = 128;
	wh[1] = 128;
	max_hp = 30;
	speed = 4;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/enemy_middle1.png"));
}
void middle1::move(enemy* enem) {
	if (enem->e_sdl.x + enem->e_sdl.w > WINDOW_WIDTH - 80)
		enem->e_sdl.set_slope(-1, 0);
	if (enem->e_sdl.x < 80)
		enem->e_sdl.set_slope(1, 0);
	enem->e_sdl.linear_move(4);
}

void middle1::how_to_fire(enemy* enem) {
	if (enem->get_fire_delay()[0] <= 0) {

		Manager::get_m()->directbullet_set_coordinate(
			enem->e_sdl.x, enem->e_sdl.y,
			Manager::get_m()->get_Plr()->p_sdl.x, Manager::get_m()->get_Plr()->p_sdl.y,
			12, false
		);
		enem->get_fire_delay()[0] = 200;
	}
	if (enem->get_fire_delay()[0] == 190) {
		Manager::get_m()->nwaybullet_set_coordinate(
			enem->e_sdl.x, enem->e_sdl.y,
			Manager::get_m()->get_Plr()->p_sdl.x, Manager::get_m()->get_Plr()->p_sdl.y,
			30, 3, 7, false);

	}
	if (enem->get_fire_delay()[0] == 180) {
		Manager::get_m()->nwaybullet_set_coordinate(
			enem->e_sdl.x, enem->e_sdl.y,
			Manager::get_m()->get_Plr()->p_sdl.x, Manager::get_m()->get_Plr()->p_sdl.y,
			15, 3, 10, false);

	}
	if (enem->get_fire_delay()[0] == 100) {
		Manager::get_m()->circlebullet_set(
			enem->e_sdl.x, enem->e_sdl.y,
			16, false, 8, false);

	}
	if (enem->get_fire_delay()[0] == 80) {
		Manager::get_m()->circlebullet_set(
			enem->e_sdl.x, enem->e_sdl.y,
			21, true, 12, false);

	}
}