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
	//enemy가 어떤 종류인지는 enemy_type의 static 객체로 나타낸다, 따라서 enemy_type의 메서드들은 this의 변수를 수정하는 것이 아니라 매개변수로 enemy의 변수 주소를 입력받아 조작한다
	//이 방식을 사용하면 Manager.cpp에서 enemy 객체를 종류마다 만들고 pulling하는 대신, 10개 정도만 만들고 enemy_type만 교체해서 재사용율을 높일 수 있다
	enemy_type() { }
	void init(SDL_Rectf* rect, int* max_hp) {
		rect->w = wh[0];
		rect->h = wh[1];
		*max_hp = this->max_hp;
	}
	virtual void move(SDL_Rectf& s) {
		//자식 클래스에서 정의되지 않았다면 적들은 기본적으로 직선 이동한다
		s.linear_move(speed);
	}
	virtual void how_to_fire(SDL_Rectf e_sdl, int(&i)[4]) {
		//이 함수가 인자로 받는 배열 크기는, enemy가 가질 수 있는 공격 방식의 개수와 동일하도록 조정한다
		cout << "fire method is called by parent enemy_type. please check the method.";
	}
	virtual void type_test() { cout << "it's enemy_type\n"; }
};