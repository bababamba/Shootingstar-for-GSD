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
	//enemy�� � ���������� enemy_type�� static ��ü�� ��Ÿ����, ���� enemy_type�� �޼������ this�� ������ �����ϴ� ���� �ƴ϶� �Ű������� enemy�� ���� �ּҸ� �Է¹޾� �����Ѵ�
	//�� ����� ����ϸ� Manager.cpp���� enemy ��ü�� �������� ����� pulling�ϴ� ���, 10�� ������ ����� enemy_type�� ��ü�ؼ� �������� ���� �� �ִ�
	void init(SDL_Rectf* rect, int* max_hp);
	virtual void move(enemy* enem);
	virtual void how_to_fire(enemy* enem);
	SDL_Texture* get_texture();
	int* get_wh();

	virtual void type_test() { cout << "it's enemy_type\n"; }
};