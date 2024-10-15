#include "ItemEn.h"
void  ItemEn::Render() {

	CAnimations* animations = CAnimations::GetInstance();
	if (vx>0)
		animations->Get(13013)->Render(x, y);
	else
		animations->Get(13014)->Render(x, y);
}
void  ItemEn::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - 2 / 2;
	top = y - 2 / 2;
	right = left + 2;
	bottom = top + 2;
}
void ItemEn::OnNoCollision(DWORD dt) {
	x += vx * dt;
}
void  ItemEn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (GetTickCount64() - tg > 1000) {
		vx *= -1;
		tg = GetTickCount64();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}