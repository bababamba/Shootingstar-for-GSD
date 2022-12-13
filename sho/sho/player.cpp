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
	//�ܼ������� init �Լ� 1���� �����ϸ� �÷��̾� ��ü�� ���ο� ������ ������ �غ� �ȴ�
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
				//4�ܰ� ����
				Manager::get_m()->bullet_set(p_sdl.x, p_sdl.y + 28, 0, -1, BULLET_SPEED, true);
				Manager::get_m()->bullet_set(p_sdl.x + 64, p_sdl.y + 28, 0, -1, BULLET_SPEED, true);
			case 2:
				//3�ܰ� ����
				Manager::get_m()->directbullet_set_degree(p_sdl.x + 28, p_sdl.y + 28, 255, BULLET_SPEED, true);
				Manager::get_m()->directbullet_set_degree(p_sdl.x + 28, p_sdl.y + 28, 285, BULLET_SPEED, true);
			case 1:
				//2�ܰ� ����
				Manager::get_m()->directbullet_set_degree(p_sdl.x + 28, p_sdl.y + 28, 240, BULLET_SPEED, true);
				Manager::get_m()->directbullet_set_degree(p_sdl.x + 28, p_sdl.y + 28, 300, BULLET_SPEED, true);
			default:
				//1�ܰ� ����
				Manager::get_m()->bullet_set(p_sdl.x + 28, p_sdl.y + 28, 0, -1, BULLET_SPEED, true);
				attack_delay = 10;
		}
	}
}

void player::increse_attack_level(const int i) { 
	//attack_level�� �ִ� 3�ܰ������ �����Ѵ�
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
	//������� ����� ������ ����, R��ư ������ ����۵ȴٴ� �ؽ�Ʈ �̹���
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