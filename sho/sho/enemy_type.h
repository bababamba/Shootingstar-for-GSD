#include "SDL_Rectf.h"
#include "Manager.h"
#pragma once

#include <iostream>
using namespace std;

struct enemy_type {
protected:
	int wh[2];	//width, height
	int max_hp;
	int speed;
public:
	//enemy�� � ���������� enemy_type�� static ��ü�� ��Ÿ����, ���� enemy_type�� �޼������ this�� ������ �����ϴ� ���� �ƴ϶� �Ű������� enemy�� ���� �ּҸ� �Է¹޾� �����Ѵ�
	//�� ����� ����ϸ� Manager.cpp���� enemy ��ü�� �������� ����� pulling�ϴ� ���, 10�� ������ ����� enemy_type�� ��ü�ؼ� �������� ���� �� �ִ�
	enemy_type() { }
	void init(SDL_Rectf* rect, int* max_hp) {
		rect->w = wh[0];
		rect->h = wh[1];
		*max_hp = this->max_hp;
	}
	virtual void move(SDL_Rectf& s) {
		//�ڽ� Ŭ�������� ���ǵ��� �ʾҴٸ� ������ �⺻������ ���� �̵��Ѵ�
		s.linear_move(speed);
	}
	virtual void how_to_fire(SDL_Rectf e_sdl, int(&i)[4]) {
		//�� �Լ��� ���ڷ� �޴� �迭 ũ���, enemy�� ���� �� �ִ� ���� ����� ������ �����ϵ��� �����Ѵ�
		cout << "fire method is called by parent enemy_type. please check the method.";
	}
	virtual void type_test() { cout << "it's enemy_type\n"; }
};