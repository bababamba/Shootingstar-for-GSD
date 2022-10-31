#include "SDL.h"
#include "SDL_image.h"
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include "SDL_Rectf.h"
#include "rapidjson/document.h"
using namespace std;

#pragma once
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540

class enemy;
class player;
struct basic;
class Manager {
public:
	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	int amain(int argv, char** args);
	//bool rectcol(SDL_Rectf a, SDL_Rectf b);
	bool rectcolf(SDL_Rectf a, SDL_Rectf b);
	void render();
	void close();

	void bullet_set(float x, float y, float slope_x, float slope_y, bool is_players);
	void enemy_set(float x, float y, float slope_x, float slope_y, int enemy_code);
	void item_set(float x, float y);
	player* get_Plr() { 
		return Plr; 
	}

	void stage_load();
	
	static Manager* get_m();
private:
	//싱글톤
	Manager();
	//~Manager();
	static Manager* m;
	
	rapidjson::Document cur_stage;
	int cur_enemy_num;
	int last_enemy_num;
	bool is_enemy_generating;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screenL;
	SDL_Texture* texture;
	SDL_Texture* bultexture;

	//적 종류, enemy를 배치할 때 set_type에 매개변수로 집어넣어 사용한다
	basic* srct_basic;

	//플레이어 혹은 상대방이 공격한다면, available bullets에서 pop한 Rect를 공격한 객체에 해당하는 list로 옮겨준다
	//bullet이 화면 밖으로 나갔다면, 다시 availble_bullets에 push한다
	stack<SDL_Rectf*> available_bullets;
	vector<SDL_Rectf*> enemy_bullets;
	vector<SDL_Rectf*> player_bullets;

	stack<enemy*> available_enemy;
	vector<enemy*> cur_enemy;

	stack<SDL_Rectf*> available_items;
	vector<SDL_Rectf*> cur_items;

	player* Plr;
	bool pgun = false;
	bool dir[4] = { false , false , false , false };
	int speed = 8;
	int bulcount = 0;
	int pgundelay = 3;

	bool eGun[20] = { false };
	int eGunDelay[20] = { 0 };
	float eBulSpeed = 5;
	int eBulCount = 0;
	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
};
