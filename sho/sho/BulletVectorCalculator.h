#pragma once

class BulletVectorCalculator {
public:
	static void InitAimingBullet(float mx, float my, float ex, float ey, float &vx, float& vy);   //¡∂¡ÿ≈∫
	static void InitDirectedBullet(float ex, float ey, float& vx, float& vy, float theta); //πÊ«‚≈∫
	static void InitNWayBullets(float vx0, float vy0, float theta, int n, float vx[], float vy[]);    //n-way, »ÆªÍ≈∫
	static void InitCircleBullets(int n, bool odd, float vx[], float vy[]);  //ø¯«¸≈∫
	static void RotateVelocity(float theta, float vx0, float vy0, float& vx, float& vy);
	static float SlopeToDegree(float x, float y); //πÊ«‚ ∫§≈Õ∏¶ ∞¢µµ∑Œ ∫Ø»Ø
};