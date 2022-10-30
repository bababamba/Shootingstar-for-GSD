#include <math.h>

#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540
#pragma once

struct SDL_Rectf {
public:
	float slope[2];	//만약 이 Rect가 직선 이동 중이라면, 길이가 1로 표준화된 벡터 slope가 그 이동 방향을 표시한다 (SDL에서 위로 이동할 경우 y 좌표가 감소함에 유의)
	float x, y;
	float w, h;

	//slope의 인덱스를 초기화할 때에 어떤 값을 넣는지는 상관없으나 꼭 set_slope를 호출하도록 해야 한다, set_slope가 초기화해주지 않으면 linear_move의 speed가 제대로 적용되지 않는다
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