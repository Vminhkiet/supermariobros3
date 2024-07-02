#include "Bullet.h"

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += vx * dt;
	y += vy * dt;
}
void CBullet::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(11100)->Render(x, y,10,10);
}
void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 10 / 2;
	t = y - 10 / 2;
	r = l + 10;
	b = t + 10;
}
