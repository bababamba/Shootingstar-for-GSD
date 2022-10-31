#include "BulletVectorCalculator.h"
#include <math.h>
#define M_PI 3.14

//조준탄 
//내부에서 정규화를 거침
void BulletVectorCalculator::InitAimingBullet(
	float mx, float my,  // 도착 지점의 좌표
	float ex, float ey,	 // 발사 지점의 좌표
	float& vx, float& vy // 탄의 방향 벡터
) {
	// 목표까지의 거리 d를 구하기
	float d = sqrt((mx - ex) * (mx - ex) + (my - ey) * (my - ey));

	// 속도가 일정한 값(speed)이 되도록 속도벡터를 구하기:
	// 목표까지의 거리 d가 0일 때는 아랫쪽으로 발사함
	if (d) {
		vx = (mx - ex) / d;
		vy = (my - ey) / d;
	}
	else {
		vx = 0;
		vy = 1;
	}
}

//방향탄 
//내부에서 정규화를 거침
void BulletVectorCalculator::InitDirectedBullet(
	float ex, float ey,    // 발사 지점의 좌표
	float& vx, float& vy,  // 탄의 방향 벡터
	float theta            // 발사각도
) {
	// speed의 속도로 각도 theta 방향으로 날아가는 탄의 속도벡터(vx,vy)를 구하기:
	// M_PI는 원주율
	vx = cos(M_PI / 180 * theta);
	vy = sin(M_PI / 180 * theta);
}

//확산탄 
//내부에서 정규화를 거침
void BulletVectorCalculator::InitNWayBullets(
	float vx0, float vy0,    // 중심이 되는 탄의 속도
	float theta,             // 탄과 탄사이의 각도
	int n,                   // 탄의 갯수
	float vx[], float vy[]   // n-way탄의 속도
) {
	// 탄과 탄 사이의 각도를 라디안으로 변환하기
	float rad_step = M_PI / 180 * theta;

	// 가장자리의 탄과 중심 부분의 탄의 각도를 계산하기
	float rad = n % 2 ? -n / 2 * rad_step : (-n / 2 + 0.5) * rad_step;

	// n개의 탄의 속도를 계산하기
	for (int i = 0; i < n; i++, rad += rad_step) {

		// (vx[i],vy[i])를 구하기:
		// 속도 벡터 (vx0,vy0)를 rad만큼 회전시키기.
		float c = cos(rad), s = sin(rad);
		vx[i] = vx0 * c - vy0 * s;
		vy[i] = vx0 * s + vy0 * c;
	}
}

//원형탄 
//내부에서 정규화를 거침
void BulletVectorCalculator::InitCircleBullets(
	int n,                   // 탄의 갯수
	bool odd,                // 홀수 패턴일 때 참
	float vx[], float vy[]   // 원형탄의 방향벡터
) {
	// 탄과 탄 사이의 각도를 계산하기
	float rad_step = M_PI * 2 / n;

	// 최초의 탄의 각도를 계산하기:
	// 홀수 패턴일 때는 rad_step/2만큼 틀어줌.
	float rad = odd ? rad_step / 2 : 0;

	// n개의 탄의 속도벡터를 구하기:
	// speed의 속도로 각도 rad 방향으로 날아가는 탄의 속도벡터를 구하기
	// 원형탄을 날리는 처리를 응용한 것
	for (int i = 0; i < n; i++, rad += rad_step) {
		vx[i] = cos(rad);
		vy[i] = sin(rad);
	}
}

void BulletVectorCalculator::RotateVelocity(
	float theta,           // 회전 각도
	float vx0, float vy0,  // 원래 속도
	float& vx, float& vy   // 회전후의 속도
) {
	// theta를 라디안으로 변환하여 cos과 sin값을 구하기:
	// M_PI는 원주율.
	float rad = M_PI / 180 * theta;
	float c = cos(rad), s = sin(rad);

	// 속도벡터 (vx0,vy0)를 회전시킨 (vx,vy)를 구하기
	vx = vx0 * c - vy0 * s;
	vy = vx0 * s + vy0 * c;
}

//방향벡터를 각도로 변환
//기준 좌표는 x = 1.0, y = 0.0 에서 시계방향으로 +
float BulletVectorCalculator::SlopeToDegree(
	float x, float y	//방향 벡터
) {
	// 기준 벡터 생성
	float cx = 1.0, cy = 0.0;

	//매개변수로 받은 벡터를 기준 벡터와 내적
	float dot = (cx * x) + (cy * y);

	//매개변수로 받은 벡터의 크기 구하기
	float length = sqrt((x * x) + (y * y));
	
	//arccos으로 라디안 값 연산
	float radian = acos( dot / (1 * length) );

	//라디안값을 디그리로 변환해 리턴
	return radian * (180 / M_PI);
}