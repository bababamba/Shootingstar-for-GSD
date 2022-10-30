#include <math.h>

#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540
#pragma once

struct SDL_Rectf {
public:
	float slope[2];	//���� �� Rect�� ���� �̵� ���̶��, ���̰� 1�� ǥ��ȭ�� ���� slope�� �� �̵� ������ ǥ���Ѵ� (SDL���� ���� �̵��� ��� y ��ǥ�� �����Կ� ����)
	float x, y;
	float w, h;

	//slope�� �ε����� �ʱ�ȭ�� ���� � ���� �ִ����� ��������� �� set_slope�� ȣ���ϵ��� �ؾ� �Ѵ�, set_slope�� �ʱ�ȭ������ ������ linear_move�� speed�� ����� ������� �ʴ´�
	void init(float x, float y, float w, float h, float slope_x = 0, float slope_y = -1) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		set_slope(slope_x, slope_y);
	}
	void set_slope(float slope_x, float slope_y) { 
		float norm = sqrt((slope_x * slope_x) + (slope_y * slope_y));
		slope[0] = slope_x / norm;
		slope[1] = slope_y / norm;
	}
	void linear_move(int speed) {
		x += speed * slope[0];
		y += speed * slope[1];
	}
	bool is_out() {
		return (x < 0 - w / 2) | (x > WINDOW_WIDTH + w / 2) | (y < 0 - h / 2) | (y > WINDOW_HEIGHT + h / 2);
	}
	/*
	bool is_very_out() {
		return (x < -200) | (x > WINDOW_WIDTH + 200) | (y < 200) | (y > WINDOW_HEIGHT + 200);
	}*/
};