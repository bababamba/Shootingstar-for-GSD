#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include "enemy.h"
#include "Manager.h"
#include "SDL_Rectf.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screenL;
SDL_Texture* texture;
SDL_Texture* bultexture;

int main(int argv, char** args) {
	Manager* m = Manager::get_m();
	m->amain(argv, args);

	return 0; 
}