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

void player::attack() { 
	//★공격 함수 불러와서 공격, attack_level에 switch문 사용해서 공격 단계 구현
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