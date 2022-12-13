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

	//�߰� : ������
	Boss1* boss1instance;
	bool boss1battle = false;
	player& getPlayer();

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

	//�� ����, enemy�� ��ġ�� �� set_type�� �Ű������� ����־� ����Ѵ�
	basic* srct_basic;
	zigzag* srct_zigzag;
	charger* srct_charger;
	middle1* srct_middle1;
	BEEG* srct_BEEG;
	Fixed* srct_fixed;
	//�÷��̾� Ȥ�� ������ �����Ѵٸ�, available bullets���� pop�� Rect�� ������ ��ü�� �ش��ϴ� list�� �Ű��ش�
	//bullet�� ȭ�� ������ �����ٸ�, �ٽ� availble_bullets�� push�Ѵ�
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
