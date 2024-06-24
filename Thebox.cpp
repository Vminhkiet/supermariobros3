#include "Thebox.h"
void Thebox::Render()
{
	RenderBoundingBox();
}
void Thebox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	roi = false;
	if (vy > 0 && count==0) {
		roi = true;
	}
	if(!roi)
	    vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void Thebox::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->obj->IsBlocking()) {
		if (e->ny < 0) {
			vy = 0;
			if(count == -1)
			    count++;
		}
		
	}
}
void Thebox::OnNoCollision(DWORD dt)
{
	if (!roi) {
		y += vy * dt;
		x += vx * dt;
	}
};
void Thebox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - THEBOX_WIDTH / 2;
	t = y - THEBOX_HEIGHT / 2;
	r = l + THEBOX_WIDTH;
	b = t + THEBOX_HEIGHT;
}