#include "Manager.h"
#include "boss1.h"
#include "boss1_left.h"
#include "boss1_right.h"
#include "boss1_core.h"

Boss1::Boss1(SDL_Renderer* M_renderer) {
	has_item = false;
	left_parts = new boss1_left(M_renderer);
	right_parts = new boss1_right(M_renderer);
	core_parts = new boss1_core(M_renderer);

	lefthp = 20;
	righthp = 15;
	corehp = 30;

	left_pos[0] = 100;
	left_pos[1] = 100;
	right_pos[0] = 360;
	right_pos[1] = 100;
	core_pos[0] = 250;
	core_pos[1] = 120;

	e_sdl.x = 100;
	e_sdl.y = 100;
	e_sdl.set_slope(0.0f, 0.0f);

	permit_fire = false;
}

void Boss1::init() {
	lefthp = 20;
	righthp = 15;
	corehp = 30;
	permit_fire = false;
	left_parts->SetCrash(false);
	right_parts->SetCrash(false);
	core_parts->SetOpen(false);
	fire_delay[0] = -5.0f;
	fire_delay[1] = -5.0f;
	fire_delay[2] = -5.0f;

	fire_delay[3] = -5.0f;
}

Boss1::~Boss1() {
	delete left_parts;
	delete right_parts;
	delete core_parts;
}
void Boss1::render() {
	e_type->render(e_sdl);

	SDL_Rectf temp = e_sdl;
	temp.x += left_pos[0];
	temp.y += left_pos[1];
	left_parts->render(temp);

	temp = e_sdl;
	temp.x += right_pos[0];
	temp.y += right_pos[1];
	right_parts->render(temp);

	temp = e_sdl;
	temp.x += core_pos[0];
	temp.y += core_pos[1];
	core_parts->render(temp);
}

void Boss1::fire() {
	if (permit_fire) {
		firedelaycheck += (60.0f * Manager::get_m()->getdeltaTime());
		while (firedelaycheck >= 1.0f)
		{
			firedelaycheck -= 1.0f;
			for (int i = 0; i < 4; i++) {
				if (fire_delay[i]-- < -10)
					break;
			}
			if (lefthp > 0)
				left_parts->how_to_fire(this);
			if (righthp > 0)
				right_parts->how_to_fire(this);
			if (core_Exposure)
				core_parts->how_to_fire(this);
		}
	}
}

void Boss1::move() {
	e_type->move(this);
}

bool Boss1::hit() {
	if (core_Exposure && corehp <= 0)
	{
		die();
		return true;
	}
	return false;
}

void Boss1::die() {
	
	//클리어 코드를 넣자
}

void Boss1::set_type(enemy_type* para_type) {
	for (int i = 0; i < 4; i++) {
		fire_delay[i] = 5;
	}
	SA_var1 = -1;
	SA_var2 = -1;
	SA_bool = false;
	e_sdl.set_speed(0);
	if (para_type == nullptr) {
		e_type = nullptr;
		return;
	}
	e_type = para_type;
	e_type->init(&e_sdl, &hp);
}

bool Boss1::CollisionTest(SDL_Rectf b_sdl) {
	SDL_Rectf temp = e_sdl;
	bool hit = false;
	int* wh;
	if (lefthp > 0)
	{
		temp = e_sdl;
		temp.x += left_pos[0];
		temp.y += left_pos[1];
		wh = left_parts->get_wh();
		temp.w = wh[0];
		temp.h = wh[1];
		if (Manager::get_m()->rectcolf(temp, b_sdl)) {
			lefthp--;
			hit = true;
			if (lefthp <= 0)
				left_parts->SetCrash(true);
		}
	}
	if (righthp > 0)
	{
		temp = e_sdl;
		temp.x += right_pos[0];
		temp.y += right_pos[1];
		wh = right_parts->get_wh();
		temp.w = wh[0];
		temp.h = wh[1];
		if (Manager::get_m()->rectcolf(temp, b_sdl)) {
			righthp--;
			hit = true;
			if (righthp <= 0)
				right_parts->SetCrash(true);
		}
	}

	if (core_Exposure && corehp > 0) {
		temp = e_sdl;
		temp.x += core_pos[0];
		temp.y += core_pos[1];
		wh = core_parts->get_wh();
		temp.w = wh[0];
		temp.h = wh[1];
		if (Manager::get_m()->rectcolf(temp, b_sdl)) {
			corehp--;
			hit = true;
		}
	}

	if (!core_Exposure && lefthp <= 0 && righthp <= 0) {
		core_Exposure = true;
		core_parts->SetOpen(true);
		fire_delay[0] = -5.0f;
		fire_delay[1] = -5.0f;
		fire_delay[2] = -5.0f;
		fire_delay[3] = -5.0f;
	}
	return hit;
}