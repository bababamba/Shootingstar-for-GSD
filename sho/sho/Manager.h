#include "SDL.h"
#include "SDL_image.h"
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include "SDL_Rectf.h"
#include "rapidjson/document.h"
using namespace std;
#include <iostream>

#pragma once
#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 960

class enemy;
class player;
struct basic;
struct zigzag;
struct charger;
struct middle1;
struct BEEG;
struct Fixed;
class Bullet;
class Boss1;

class Manager {
public:
	int amain(int argv, char** args);
	//bool rectcol(SDL_Rectf a, SDL_Rectf b);
	bool rectcolf(SDL_Rectf a, SDL_Rectf b);
	void init();
	void render();
	void close();

	void bullet_set(float x, float y, float slope_x, float slope_y, int speed, bool is_players);
	void enemy_set(float x, float y, float slope_x, float slope_y, int enemy_code, bool item);
	void item_set(float x, float y);
	player* get_Plr() {
		return Plr;
	}
	SDL_Renderer* get_renderer() {
		return renderer;
	};

	void stage_load();
	
	static Manager* get_m();

	//추가 : 조대훈
	Boss1* boss1instance;
	bool boss1battle = false;
	player& getPlayer();

	//deltaTime을 리턴
	float getdeltaTime() { return deltaTime; }
	//도착 지점을 인수로 받는 방향탄 생성 함수
	void directbullet_set_coordinate(float start_x, float start_y, float end_x, float end_y, int speed, bool is_players);
	//발사 각도를 인수로 받는 방향탄 생성 함수. 
	void directbullet_set_degree(float start_x, float start_y, float theta, int speed, bool is_players);
	//원형탄 생성 함수. 
	void circlebullet_set(float start_x, float start_y, int n, bool odd, int speed, bool is_players);
	//중심 탄의 방향을 각도로 받는 확산탄 생성 함수. 
	void nwaybullet_set_degree(float start_x, float start_y, float central_angle, float theta, int n, int speed, bool is_players);
	//중심 탄의 도착 지점을 인수로 받는 확산탄 생성 함수. 
	void nwaybullet_set_coordinate(float start_x, float start_y, float end_x, float end_y, float theta, int n, int speed, bool is_players);
	//중심 탄의 방향 벡터를 받는 확산탄 생성 함수. 
	void nwaybullet_set_slope(const float start_x, const float start_y, const float slope_x, const float slope_y, float theta, int n, int speed, bool is_players);

private:
	//싱글톤
	Manager(const char* title, int xpos, int ypos, int height, int width, int flags);
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
	SDL_Texture* ebultexture;
	SDL_Texture* item_texture;
	SDL_Texture* back_texture;

	//적 종류, enemy를 배치할 때 set_type에 매개변수로 집어넣어 사용한다
	basic* srct_basic;
	zigzag* srct_zigzag;
	charger* srct_charger;
	middle1* srct_middle1;
	BEEG* srct_BEEG;
	Fixed* srct_fixed;
	//플레이어 혹은 상대방이 공격한다면, available bullets에서 pop한 Rect를 공격한 객체에 해당하는 list로 옮겨준다
	//bullet이 화면 밖으로 나갔다면, 다시 availble_bullets에 push한다
	stack<Bullet*> available_bullets;
	vector<Bullet*> enemy_bullets;
	vector<Bullet*> player_bullets;

	stack<enemy*> available_enemy;
	vector<enemy*> cur_enemy;

	stack<SDL_Rectf*> available_items;
	vector<SDL_Rectf*> cur_items;

	vector<SDL_Rectf*> background;

	player* Plr;
	bool pgun = false;
	bool dir[4] = { false , false , false , false };
	int speed = 353;

	unsigned int prev_time = SDL_GetTicks();
	unsigned int current_time = SDL_GetTicks();
	float deltaTime = 0.0f;
};
