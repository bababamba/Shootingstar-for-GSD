#pragma once
#include <iostream>
using namespace std;

class enemy;
class SDL_Texture;
struct enemy_type {
protected:
	int wh[2];	//width, height
	int max_hp;
	int speed;
	SDL_Texture* e_texture;
public:
	//enemy가 어떤 종류인지는 enemy_type의 static 객체로 나타낸다, 따라서 enemy_type의 메서드들은 this의 변수를 수정하는 것이 아니라 매개변수로 enemy의 변수 주소를 입력받아 조작한다
	//이 방식을 사용하면 Manager.cpp에서 enemy 객체를 종류마다 만들고 pulling하는 대신, 10개 정도만 만들고 enemy_type만 교체해서 재사용율을 높일 수 있다
	void init(SDL_Rectf* rect, int* max_hp);
	virtual void move(enemy* enem);
	virtual void how_to_fire(enemy* enem);
	SDL_Texture* get_texture();
	int* get_wh();

	virtual void type_test() { cout << "it's enemy_type\n"; }
};