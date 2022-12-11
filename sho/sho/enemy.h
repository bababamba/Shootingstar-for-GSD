#pragma once
#include "SDL_Rectf.h"
#include "enemy_type.h"

class enemy {
private:
	int hp;
	int fire_delay[4];	//공격 딜레이, 강력한 적들은 2~4개 정도의 공격 방식을 가지므로 배열이다
	float firedelaycheck = 0.0f;
	bool has_item;

	//적의 특징을 만드는데 사용할 다용도 변수 (Swiss Army variable)
	int SA_var1 = -1;
	int SA_var2 = -1;
	bool SA_bool = false;

	enemy_type* e_type;
public:
	SDL_Rectf e_sdl;
	//enemy();

	void render();
	void fire();
	void move();
	bool hit();
	void die();
	void set_type(enemy_type* para_type);
	SDL_Rectf getCollisonRectf();
	//bool CollisonTest(Bullet& );
	enemy_type* get_type() { 
		return e_type;
	}
	void test() { 
		e_type->type_test(); 
	}

	//C++에서 배열이 매개변수로 전달되면 그 배열의 0번 인덱스의 주소만 넘어간다, 반환할 때에도 마찬가지다
	int* get_fire_delay() { return fire_delay; }
	void set_has_item(bool b) { has_item = b; }
	void set_SA_var1(int i) { SA_var1 = i; }
	void set_SA_var2(int i) { SA_var2 = i; }
	void set_SA_bool(bool b) { SA_bool = b; }
	int get_SA_var1() { return SA_var1; }
	int get_SA_var2() { return SA_var2; }
	bool get_SA_bool() { return SA_bool; }
};