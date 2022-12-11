#pragma once
#include "SDL_Rectf.h"
#include "enemy_type.h"
#include "Manager.h"
#include "charger.h"
#include "enemy.h"
#include "player.h"

charger::charger(SDL_Renderer* M_renderer) {
	wh[0] = 64;
	wh[1] = 64;
	max_hp = 3;
	speed = 600;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/enemy_charger.png"));
}

void charger::move(enemy* enem) {
	//SA_var1은 speed를 나타낸다
	if( !enem->get_SA_bool()) {
		enem->set_SA_var1(speed);
		enem->set_SA_bool(true);
	}
	enem->e_sdl.linear_move();
	if( (enem->get_fire_delay()[0] < 0) & (enem->get_SA_var1() > 0) ) {
		enem->get_fire_delay()[0] = 5;
		enem->set_SA_var1(enem->get_SA_var1() - 60);
		enem->e_sdl.set_speed(enem->get_SA_var1());
	} else if( (enem->get_fire_delay()[0] < -30) & (enem->get_SA_var1() == 0) ) {
		enem->set_SA_var1(-1);
		enem->e_sdl.set_speed(speed);
		enem->e_sdl.set_slope(Manager::get_m()->get_Plr()->p_sdl.x - enem->e_sdl.x, Manager::get_m()->get_Plr()->p_sdl.y - enem->e_sdl.y);
	}
}

void charger::render(SDL_Rectf& sdl)
{
	SDL_Rect temp;
	temp.x = round(sdl.x);
	temp.y = round(sdl.y);
	temp.w = round(sdl.w);
	temp.h = round(sdl.h);
	SDL_RenderCopy(Manager::get_m()->get_renderer(), e_texture, NULL, &temp);
}