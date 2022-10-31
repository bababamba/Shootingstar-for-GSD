#include "BulletVectorCalculator.h"
#include <math.h>
#define M_PI 3.14

//����ź 
//���ο��� ����ȭ�� ��ħ
void BulletVectorCalculator::InitAimingBullet(
	float mx, float my,  // ���� ������ ��ǥ
	float ex, float ey,	 // �߻� ������ ��ǥ
	float& vx, float& vy // ź�� ���� ����
) {
	// ��ǥ������ �Ÿ� d�� ���ϱ�
	float d = sqrt((mx - ex) * (mx - ex) + (my - ey) * (my - ey));

	// �ӵ��� ������ ��(speed)�� �ǵ��� �ӵ����͸� ���ϱ�:
	// ��ǥ������ �Ÿ� d�� 0�� ���� �Ʒ������� �߻���
	if (d) {
		vx = (mx - ex) / d;
		vy = (my - ey) / d;
	}
	else {
		vx = 0;
		vy = 1;
	}
}

//����ź 
//���ο��� ����ȭ�� ��ħ
void BulletVectorCalculator::InitDirectedBullet(
	float ex, float ey,    // �߻� ������ ��ǥ
	float& vx, float& vy,  // ź�� ���� ����
	float theta            // �߻簢��
) {
	// speed�� �ӵ��� ���� theta �������� ���ư��� ź�� �ӵ�����(vx,vy)�� ���ϱ�:
	// M_PI�� ������
	vx = cos(M_PI / 180 * theta);
	vy = sin(M_PI / 180 * theta);
}

//Ȯ��ź 
//���ο��� ����ȭ�� ��ħ
void BulletVectorCalculator::InitNWayBullets(
	float vx0, float vy0,    // �߽��� �Ǵ� ź�� �ӵ�
	float theta,             // ź�� ź������ ����
	int n,                   // ź�� ����
	float vx[], float vy[]   // n-wayź�� �ӵ�
) {
	// ź�� ź ������ ������ �������� ��ȯ�ϱ�
	float rad_step = M_PI / 180 * theta;

	// �����ڸ��� ź�� �߽� �κ��� ź�� ������ ����ϱ�
	float rad = n % 2 ? -n / 2 * rad_step : (-n / 2 + 0.5) * rad_step;

	// n���� ź�� �ӵ��� ����ϱ�
	for (int i = 0; i < n; i++, rad += rad_step) {

		// (vx[i],vy[i])�� ���ϱ�:
		// �ӵ� ���� (vx0,vy0)�� rad��ŭ ȸ����Ű��.
		float c = cos(rad), s = sin(rad);
		vx[i] = vx0 * c - vy0 * s;
		vy[i] = vx0 * s + vy0 * c;
	}
}

//����ź 
//���ο��� ����ȭ�� ��ħ
void BulletVectorCalculator::InitCircleBullets(
	int n,                   // ź�� ����
	bool odd,                // Ȧ�� ������ �� ��
	float vx[], float vy[]   // ����ź�� ���⺤��
) {
	// ź�� ź ������ ������ ����ϱ�
	float rad_step = M_PI * 2 / n;

	// ������ ź�� ������ ����ϱ�:
	// Ȧ�� ������ ���� rad_step/2��ŭ Ʋ����.
	float rad = odd ? rad_step / 2 : 0;

	// n���� ź�� �ӵ����͸� ���ϱ�:
	// speed�� �ӵ��� ���� rad �������� ���ư��� ź�� �ӵ����͸� ���ϱ�
	// ����ź�� ������ ó���� ������ ��
	for (int i = 0; i < n; i++, rad += rad_step) {
		vx[i] = cos(rad);
		vy[i] = sin(rad);
	}
}

void BulletVectorCalculator::RotateVelocity(
	float theta,           // ȸ�� ����
	float vx0, float vy0,  // ���� �ӵ�
	float& vx, float& vy   // ȸ������ �ӵ�
) {
	// theta�� �������� ��ȯ�Ͽ� cos�� sin���� ���ϱ�:
	// M_PI�� ������.
	float rad = M_PI / 180 * theta;
	float c = cos(rad), s = sin(rad);

	// �ӵ����� (vx0,vy0)�� ȸ����Ų (vx,vy)�� ���ϱ�
	vx = vx0 * c - vy0 * s;
	vy = vx0 * s + vy0 * c;
}

//���⺤�͸� ������ ��ȯ
//���� ��ǥ�� x = 1.0, y = 0.0 ���� �ð�������� +
float BulletVectorCalculator::SlopeToDegree(
	float x, float y	//���� ����
) {
	// ���� ���� ����
	float cx = 1.0, cy = 0.0;

	//�Ű������� ���� ���͸� ���� ���Ϳ� ����
	float dot = (cx * x) + (cy * y);

	//�Ű������� ���� ������ ũ�� ���ϱ�
	float length = sqrt((x * x) + (y * y));
	
	//arccos���� ���� �� ����
	float radian = acos( dot / (1 * length) );

	//���Ȱ��� ��׸��� ��ȯ�� ����
	return radian * (180 / M_PI);
}