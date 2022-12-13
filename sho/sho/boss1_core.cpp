#include "Manager.h"
#include "boss1_core.h"
#include "enemy.h"
#include "player.h"

boss1_core::boss1_core(SDL_Renderer* M_renderer) {
	wh[0] = 40;
	wh[1] = 40;
	max_hp = 30;
	speed = 0;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/boss1_core.png"));
	close_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/boss1_core_close.png"));;
	open = false;
}
void boss1_core::how_to_fire(enemy* enem) {
	int* fire_delay = enem->get_fire_delay();
	int w = 32;
	int h = 32;
	Manager* m = Manager::get_m();

	int start_x = enem->e_sdl.x + 250 + 18;
	int start_y = enem->e_sdl.y + 120 + 18;

	if (fire_delay[0] <= 0)
	{
		fire_delay[0]= 1200;
	}

	if (fire_delay[1] <= 0 && fire_delay[0] > 600 )
	{
		fire_delay[1]=50;
	}
	else if (fire_delay[1] == 30)
	{
		m->nwaybullet_set_degree(start_x, start_y, 30, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 50, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 70, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 90, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 110, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 130, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 150, 2, 5, 480, false);
	}
	else if (fire_delay[1] == 5)
	{
		plr = m->getPlayer().p_sdl;
		m->nwaybullet_set_degree(start_x, start_y, 40, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 60, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 80, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 100, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 120, 2, 5, 480, false);
		m->nwaybullet_set_degree(start_x, start_y, 140, 2, 5, 480, false);

		m->nwaybullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 3, 3, 240, false);
		//m->directbullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 240, false);
	}

	if (fire_delay[1] <= 0 && fire_delay[0] <= 600)
	{
		fire_delay[1] = 600;
	}
	else if (fire_delay[1] >= 360 && fire_delay[1] <= 480 && fire_delay[1] % 2 == 0)
	{
		m->nwaybullet_set_degree(start_x, start_y, 0, 20, 18, 600, false);
	}
	else if (fire_delay[1] >= 240 && fire_delay[1] <= 360 && fire_delay[1] % 2 == 0)
	{
		m->nwaybullet_set_degree(start_x, start_y, -(fire_delay[1] - 360) / 1.5f, 20, 18, 600, false);
	}
	else if (fire_delay[1] >= 120 && fire_delay[1] <= 240 && fire_delay[1] % 2 == 0) {
		m->nwaybullet_set_degree(start_x, start_y, 80, 20, 18, 600, false);
	}
}

void boss1_core::move(enemy* enem) {
	//이 객체는 이동하지 않는다.
}
void boss1_core::render(SDL_Rectf& sdl) {
	SDL_Rect temp;
	temp.x = round(sdl.x);
	temp.y = round(sdl.y);
	temp.w = round(wh[0]);
	temp.h = round(wh[1]);
	if(open)
		SDL_RenderCopy(Manager::get_m()->get_renderer(), e_texture, NULL, &temp);
	else
		SDL_RenderCopy(Manager::get_m()->get_renderer(), close_texture, NULL, &temp);
}

void boss1_core::SetOpen(bool s)
{
	open = s;
}