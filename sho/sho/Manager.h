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

	void bullet_set(float x, float y, float slope_x, float slope_y, int speed, bool is_players);
	void enemy_set(float x, float y, float slope_x, float slope_y, int enemy_code);
	void item_set(float x, float y);
	player* get_Plr() { 
		return Plr; 
	}

	void stage_load();
	
	static Manager* get_m();

	//�߰� : ������
	
	//deltaTime�� ����
	float getdeltaTime() { return deltaTime; }
	//���� ������ �μ��� �޴� ����ź ���� �Լ�
	void directbullet_set_coordinate(float start_x, float start_y, float end_x, float end_y, int speed, bool is_players);
	//�߻� ������ �μ��� �޴� ����ź ���� �Լ�. 
	void directbullet_set_degree(float start_x, float start_y, float theta, int speed, bool is_players);
	//����ź ���� �Լ�. 
	void circlebullet_set(float start_x, float start_y, int n, bool odd, int speed, bool is_players);
	//�߽� ź�� ������ ������ �޴� Ȯ��ź ���� �Լ�. 
	void nwaybullet_set_degree(float start_x, float start_y, float central_angle, float theta, int n, int speed, bool is_players);
	//�߽� ź�� ���� ������ �μ��� �޴� Ȯ��ź ���� �Լ�. 
	void nwaybullet_set_coordinate(float start_x, float start_y, float end_x, float end_y, float theta, int n, int speed, bool is_players);
	//�߽� ź�� ���� ���͸� �޴� Ȯ��ź ���� �Լ�. 
	void nwaybullet_set_slope(const float start_x, const float start_y, const float slope_x, const float slope_y, float theta, int n, int speed, bool is_players);

private:
	//�̱���
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

	//�� ����, enemy�� ��ġ�� �� set_type�� �Ű������� ����־� ����Ѵ�
	basic* srct_basic;

	//�÷��̾� Ȥ�� ������ �����Ѵٸ�, available bullets���� pop�� Rect�� ������ ��ü�� �ش��ϴ� list�� �Ű��ش�
	//bullet�� ȭ�� ������ �����ٸ�, �ٽ� availble_bullets�� push�Ѵ�
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
	unsigned int prev_time = SDL_GetTicks();
	unsigned int current_time = SDL_GetTicks();
	float deltaTime = 0.0f;
};
