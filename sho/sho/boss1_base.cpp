#include "Manager.h"
#include "boss1_base.h"
#include "enemy.h"
#include "boss1.h"

boss1_base::boss1_base(SDL_Renderer* M_renderer) {
	wh[0] = 540;
	wh[1] = 160;
	max_hp = 0;
	speed = 0;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/boss1_base.png"));
}
void boss1_base::move(enemy* enem) {
	if(Manager::get_m()->cleard)
		enem->e_sdl.y -= 1;
	else if( enem->e_sdl.y < 100)
		enem->e_sdl.y += 1;
}
void boss1_base::render(SDL_Rectf& sdl) {
	SDL_Rect temp;
	temp.x = round(sdl.x);
	temp.y = round(sdl.y);
	temp.w = round(sdl.w);
	temp.h = round(sdl.h);
	SDL_RenderCopy(Manager::get_m()->get_renderer(), e_texture, NULL, &temp);
}