#include "Manager.h"
#include "boss1_right.h"
#include "enemy.h"
#include "player.h"

boss1_right::boss1_right(SDL_Renderer* M_renderer) {
	wh[0] = 80;
	wh[1] = 80;
	max_hp = 15;
	speed = 0;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/boss1_right.png"));
	crash_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/boss1_right_crash.png"));
	crash = false;
}
void boss1_right::how_to_fire(enemy* enem) {
	int* fire_delay = enem->get_fire_delay();
	int w = 32;
	int h = 32;
	Manager* m = Manager::get_m();

	int start_x = enem->e_sdl.x + 360 + 40;
	int start_y = enem->e_sdl.y + 100 + 60;

	if (fire_delay[1] <= 0)
	{
		plr = Manager::get_m()->getPlayer().p_sdl;
		fire_delay[1] = 60;
	}
	else if (fire_delay[1] == 40)
	{
		plr = m->getPlayer().p_sdl;
		m->directbullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 420, false);
	}
	else if (fire_delay[1] == 35)
	{
		m->directbullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 420, false);
	}													
	else if (fire_delay[1] == 30)						
	{													
		m->directbullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 420, false);
	}													
	else if (fire_delay[1] == 25)						
	{													
		m->directbullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 420, false);
	}	
	else if (fire_delay[1] == 20)
	{
		m->directbullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 420, false);
	}

	if (fire_delay[2] <= 0)
	{
		plr = Manager::get_m()->getPlayer().p_sdl;
		fire_delay[2] = 120;
	}
	else if (fire_delay[2] == 35)
	{
		m->nwaybullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 30, 4, 240, false);
	}
	else if (fire_delay[2] == 30)
	{
		m->nwaybullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 30, 4, 240, false);
	}
	else if (fire_delay[2] == 25)
	{
		m->nwaybullet_set_coordinate(start_x, start_y, plr.x + w, plr.y + h, 30, 4, 240, false);
	}
}

void boss1_right::move(enemy* enem) {
	//이 객체는 이동하지 않는다.
}
void boss1_right::render(SDL_Rectf& sdl) {
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

void boss1_right::SetCrash(bool b) {
	crash = b;
}