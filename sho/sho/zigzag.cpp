#pragma once
#include "SDL_Rectf.h"
#include "enemy_type.h"
#include "Manager.h"
#include "zigzag.h"
#include "enemy.h"
#include <math.h>
#include "player.h"

zigzag::zigzag(SDL_Renderer* M_renderer) {
	wh[0] = 64;
	wh[1] = 64;
	max_hp = 2;
	speed = 6;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/enemy_zigzag.png"));
}

void zigzag::move(enemy* enem) { 
	//SA_var1은 이동 시간을 나타낸다
	int* fd = enem->get_fire_delay();
	if( enem->get_SA_var2() == -1 ) { 
		enem->set_SA_bool((enem->e_sdl.x > 0) & (enem->e_sdl.x < WINDOW_WIDTH));
		fd[0] = 30;
		enem->set_SA_var2(0);
	}
	if ( fd[0] > 0) {
		enem->e_sdl.linear_move(speed);
	}else if (speed != 0) {
		speed = 0;
		float* temp = enem->e_sdl.slope;
		if( abs(temp[0]) == abs(temp[1]) )
			if( enem->get_SA_bool() )
				enem->e_sdl.set_slope(-temp[0], temp[1]);
			else
				enem->e_sdl.set_slope(temp[0], -temp[1]);
		else if( abs(temp[0]) > abs(temp[1]) )
			enem->e_sdl.set_slope(temp[0], -temp[1]);
		else
			enem->e_sdl.set_slope(-temp[0], temp[1]);
	} else if( fd[0] < -30 ) { 
		fd[0] = 30;
		speed = 6;
	}
}

void zigzag::how_to_fire(enemy* enem) {
	if( enem->get_fire_delay()[0] == -10 ) {
		Manager::get_m()->directbullet_set_coordinate(
			enem->e_sdl.x, enem->e_sdl.y, 
			Manager::get_m()->get_Plr()->p_sdl.x, Manager::get_m()->get_Plr()->p_sdl.y, 
			8, false
		);
	}
}