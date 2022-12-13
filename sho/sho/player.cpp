#pragma once
#include "Manager.h"
#include "player.h"

#define BULLET_SPEED 941

player::player() { 
	p_sdl = SDL_Rectf();
	p_sdl.init(0, 0, 64, 64);
	init();
}
void player::init() { 
	//단순하지만 init 함수 1번만 실행하면 플레이어 객체는 새로운 게임을 시작할 준비가 된다
	p_sdl.x = WINDOW_WIDTH / 2;
	p_sdl.y = WINDOW_HEIGHT - p_sdl.h;
	this->attack_level = 0;
}

void player::attack_delay_decrease() { 
	if( attack_delay > -10.0f )
		attack_delay -= 60.0f * Manager::get_m()->getdeltaTime() ;
}

void player::attack() { 
	if( attack_delay < 1 ) { 
		switch( attack_level ) { 
			case 3:
				//4단계 공격
				Manager::get_m()->bullet_set(p_sdl.x, p_sdl.y + 28, 0, -1, BULLET_SPEED, true);
				Manager::get_m()->bullet_set(p_sdl.x + 64, p_sdl.y + 28, 0, -1, BULLET_SPEED, true);
			case 2:
				//3단계 공격
				Manager::get_m()->directbullet_set_degree(p_sdl.x + 28, p_sdl.y + 28, 255, BULLET_SPEED, true);
				Manager::get_m()->directbullet_set_degree(p_sdl.x + 28, p_sdl.y + 28, 285, BULLET_SPEED, true);
			case 1:
				//2단계 공격
				Manager::get_m()->directbullet_set_degree(p_sdl.x + 28, p_sdl.y + 28, 240, BULLET_SPEED, true);
				Manager::get_m()->directbullet_set_degree(p_sdl.x + 28, p_sdl.y + 28, 300, BULLET_SPEED, true);
			default:
				//1단계 공격
				Manager::get_m()->bullet_set(p_sdl.x + 28, p_sdl.y + 28, 0, -1, BULLET_SPEED, true);
				attack_delay = 10;
		}
	}
}

void player::increse_attack_level(const int i) { 
	//attack_level은 최대 3단계까지만 존재한다
	attack_level += i;
	if( attack_level < 0 ) { 
		attack_level = 0;
	} else if( attack_level > 3 ) { 
		attack_level = 3;
	}
}

void player::die() { 
	p_sdl.x = WINDOW_WIDTH /2 ;
	p_sdl.y = WINDOW_HEIGHT + 10 ;
	//★재시작 기능이 구현된 이후, R버튼 누르면 재시작된다는 텍스트 이미지
}

SDL_Rectf player::getCollisonRectf() {
	SDL_Rectf temp;
	temp.x = p_sdl.x + 22;
	temp.y = p_sdl.y + 22;
	temp.w = 20;
	temp.h = 20;
	return temp;
}

void player::render() {
	SDL_Rect temp;
	temp.x = round(this->p_sdl.x);
	temp.y = round(this->p_sdl.y);
	temp.w = round(this->p_sdl.w);
	temp.h = round(this->p_sdl.h);
	SDL_RenderCopy(Manager::get_m()->get_renderer(), texture, NULL, &temp);
}

void player::SetTexture(SDL_Texture* tex) {
	texture = tex;
}