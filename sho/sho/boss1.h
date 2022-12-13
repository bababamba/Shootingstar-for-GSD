#pragma once
#include "enemy.h"

class boss1_left;
class boss1_right;
class boss1_core;

class Boss1 : public enemy{
protected:
	boss1_left* left_parts;
	boss1_right* right_parts;
	boss1_core* core_parts;

	int lefthp;
	int righthp;
	int corehp;

	float left_pos[2];
	float right_pos[2];
	float core_pos[2];

	bool core_Exposure = false;
public:
	Boss1(SDL_Renderer* M_renderer);
	~Boss1();

	bool permit_fire; // 사격 허용 변수
	void init();
	void render();
	void fire();
	void move();
	bool hit();
	void die();
	void set_type(enemy_type* para_type);
	bool CollisionTest(SDL_Rectf);
	
};
