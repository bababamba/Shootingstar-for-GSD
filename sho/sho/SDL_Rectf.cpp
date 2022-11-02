#include "SDL_Rectf.h"
#include "Manager.h"

void SDL_Rectf::linear_move() {
	float deltaTime = Manager::get_m()->getdeltaTime();
	x += speed * slope[0] * deltaTime;
	y += speed * slope[1] * deltaTime;
}

void SDL_Rectf::linear_move(int speed1) {
	float deltaTime = Manager::get_m()->getdeltaTime();
	x += speed1 * slope[0] * deltaTime;
	y += speed1 * slope[1] * deltaTime;
}