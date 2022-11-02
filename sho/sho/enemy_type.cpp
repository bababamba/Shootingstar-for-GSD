#pragma once
#include "SDL_Rectf.h"
#include "Manager.h"
#include "enemy.h"

void enemy_type::init(SDL_Rectf* rect, int* max_hp) {
	rect->w = wh[0];
	rect->h = wh[1];
	*max_hp = this->max_hp;
}
void enemy_type::move(enemy* enem){
	//자식 클래스에서 정의되지 않았다면 적들은 기본적으로 직선 이동한다
	enem->e_sdl.linear_move(speed);
}
void enemy_type::how_to_fire(enemy* enem) {
	//cout << "fire method is called by parent enemy_type. please check the method." << endl;
}

int* enemy_type::get_wh() { 
	return wh;
}

SDL_Texture* enemy_type::get_texture() {
	return e_texture;
}