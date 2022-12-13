#pragma once
#include "SDL_Rectf.h"
#include "enemy_type.h"
#include "Manager.h"
#include "fixed_enemy.h"
#include "enemy.h"
#include "player.h"

Fixed::Fixed(SDL_Renderer* M_renderer) {
	wh[0] = 48;
	wh[1] = 48;
	max_hp = 1;
	speed = 2*77 % 60;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/enemy_fixed.png"));
}

void Fixed::how_to_fire(enemy* enem) {
	if (enem->get_fire_delay()[0] <= 0) {

		Manager::get_m()->directbullet_set_coordinate(
			enem->e_sdl.x + 22,
			enem->e_sdl.y + 22,
			Manager::get_m()->getPlayer().p_sdl.x + 32,
			Manager::get_m()->getPlayer().p_sdl.y + 32,
			235 + 235/2,
			false);
		enem->get_fire_delay()[0] = 120;
	}
}

void Fixed::render(SDL_Rectf& sdl)
{
	SDL_Rect temp;
	temp.x = round(sdl.x);
	temp.y = round(sdl.y);
	temp.w = round(sdl.w);
	temp.h = round(sdl.h);
	SDL_RenderCopy(Manager::get_m()->get_renderer(), e_texture, NULL, &temp);
}