#include "Manager.h"
#include "boss1_left.h"
#include "enemy.h"
#include "player.h"

boss1_left::boss1_left(SDL_Renderer* M_renderer) {
	wh[0] = 80;
	wh[1] = 80;
	max_hp = 20;
	speed = 0;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/boss1_left.png"));
	crash_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/boss1_left_crash.png"));
	crash = false;
}
void boss1_left::how_to_fire(enemy* enem) {
	int* fire_delay = enem->get_fire_delay();
	SDL_Rectf plr = Manager::get_m()->get_Plr()->p_sdl;
	Manager* m = Manager::get_m();
	int start_x[4] = { enem->e_sdl.x + 100 + 33, enem->e_sdl.x + 100 + 33 + 15, enem->e_sdl.x + 100 + 33, enem->e_sdl.x + 100 + 33 + 15 };
	int start_y[4] = { enem->e_sdl.y + 100 + 33, enem->e_sdl.y + 100 + 33, enem->e_sdl.y + 100 + 33 + 15, enem->e_sdl.y + 100 + 33 + 15 };

	if (fire_delay[0] < 0) {
		fire_delay[0] = 300;
	}
	else if (fire_delay[0] == 220)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 25, 500, false);
		}
	}
	else if (fire_delay[0] == 210)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 35, 500, false);
		}
	}
	else if (fire_delay[0] == 200)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 45, 500, false);
		}
	}
	else if (fire_delay[0] == 190)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 55, 500, false);
		}
	}
	else if (fire_delay[0] == 180)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 65, 500, false);
		}
	}
	else if (fire_delay[0] == 170)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 75, 500, false);
		}
	}
	else if (fire_delay[0] == 160)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 85, 500, false);
		}
	}
	else if (fire_delay[0] == 150)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 95, 500, false);
		}
	}
	else if (fire_delay[0] == 140)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 105, 500, false);
		}
	}
	else if (fire_delay[0] == 130)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 115, 500, false);
		}
	}
	else if (fire_delay[0] == 120)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 105, 500, false);
		}
	}
	else if (fire_delay[0] == 110)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 95, 500, false);
		}
	}
	else if (fire_delay[0] == 100)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 85, 500, false);
		}
	}
	else if (fire_delay[0] == 90)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 75, 500, false);
		}
	}
	else if (fire_delay[0] == 80)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 65, 500, false);
		}
	}
	else if (fire_delay[0] == 70)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 55, 500, false);
		}
	}
	else if (fire_delay[0] == 60)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 45, 500, false);
		}
	}
	else if (fire_delay[0] == 50)
	{
		for (int i = 0; i < 4; i++) {
			m->directbullet_set_degree(start_x[i], start_y[i], 35, 500, false);
		}
	}

	if (fire_delay[3] <= 0)
	{
		fire_delay[3] = 60;
	}
	else if (fire_delay[3] == 45)
	{
		m->circlebullet_set(start_x[0] + 7, start_y[0] + 7, 12, true, 250, false);
	}
	else if (fire_delay[3] == 15)
	{
		m->circlebullet_set(start_x[0] + 7, start_y[0] + 7, 12, false, 250, false);
	}
}

void boss1_left::move(enemy* enem) {
	//이 객체는 이동하지 않는다.
}
void boss1_left::render(SDL_Rectf& sdl) {
	SDL_Rect temp;
	temp.x = round(sdl.x);
	temp.y = round(sdl.y);
	temp.w = round(wh[0]);
	temp.h = round(wh[1]);
	if(!crash)
		SDL_RenderCopy(Manager::get_m()->get_renderer(), e_texture, NULL, &temp);
	else
		SDL_RenderCopy(Manager::get_m()->get_renderer(), crash_texture, NULL, &temp);
}

void boss1_left::SetCrash(bool b) {
	crash = b;
}