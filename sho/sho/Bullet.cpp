#include "Manager.h"
#include "Bullet.h"


void Bullet::init(float x, float y, float w, float h) {
	b_sdl.init(x, y, w, h);
	collision_x	= 0.0f;
	collision_y = 0.0f;
	collision_w = 0.0f;
	collision_h = 0.0f;
}
void Bullet::move() {
	b_sdl.linear_move();
}

void Bullet::render() {
	SDL_Rect temp;
	temp.x = round(b_sdl.x);
	temp.y = round(b_sdl.y);
	temp.w = round(b_sdl.w);
	temp.h = round(b_sdl.h);
	SDL_RenderCopy(Manager::get_m()->get_renderer(), texture, NULL, &temp);
}

void Bullet::SetTexture(SDL_Texture* tex) {
	texture = tex;
}

SDL_Rectf Bullet::getCollisonRectf() {
	SDL_Rectf temp;
	temp = b_sdl;
	temp.x += collision_x;
	temp.y += collision_y;
	temp.w += collision_w;
	temp.h += collision_h;
	return temp;
}