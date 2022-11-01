#pragma once
#include "Manager.h"
#include "player.h"

#include <iostream>

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
	if( attack_delay > -10 )
		attack_delay--;
}

void player::attack() { 
	if( attack_delay < 1 ) { 
		switch( attack_level ) { 
			case 2:
				//3단계 공격
			case 1:
				//2단계 공격
			default:
				//1단계 공격
				Manager::get_m()->bullet_set(p_sdl.x, p_sdl.y, 0, -1, 8, true);
				attack_delay = 10;
		}
	}
}

void player::set_attack_level(const int i) { 
	//attack_level은 최대 3단계까지만 존재한다
	if( i < 0 ) { 
		attack_level = 0;
	} else if( i > 2 ) { 
		attack_level = 2;
	} else { 
		attack_level = i;
	}
}

void player::die() { 
	p_sdl.x = -1000;
	p_sdl.y = -1000;
}