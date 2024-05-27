#include "Koopa.h"
#include "TopGround.h"
void CKOOPA::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (roiy1 != -1 && roiy2 != -1) {
		if (x<roiy1 || x>roiy2) {
			if (state != LIFE) {
				roiy1 = -1;
				roiy2 = -1;
				isOnTop = 0;
			}
			else {
				isOnTop = 1;
				vx *= -1;
			}
		}
	}
	if (isOnTop) {
		isroi = 0;
	}
	if (!isOnTop)
	    vy += ay * dt;
	vx += ax * dt;

	if ((state == DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CKOOPA::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == LIFE) {
		if (vx == 0)
		{
			if (nx > 0) aniId = 13007;
			else aniId = 13006;
		}
		else if (vx > 0)
		{
			aniId = 13003;
		}
		else // vx < 0
		{
			aniId = 13002;
		}
	}
	else if (state == MAI) {
		aniId = 13004;
	}
	else if (state == MAI_MOVE) {
		aniId = 13005;
	}
	animations->Get(aniId)->Render(x, y,16,26);
}
void CKOOPA::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
void CKOOPA::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking() && e->obj->GetType() != 14) return;
	if (e->obj->GetType() != 14) {
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
	if (dynamic_cast<CTop*>(e->obj)) {
		CTop* top = dynamic_cast<CTop*>(e->obj);
		if (e->ny < 0) {
			isroi = 1;
		}
		if (e->obj->GetType() != 14) {
			if (e->ny != 0)
			{
				vy = 0;
			}
			else if (e->nx != 0)
			{
				vx = -vx;
			}
		}
		if (isroi) {
			roiy1 = top->getx();
			roiy2 = roiy1 + top->getwidth();
			vy = 0;
			y = top->Gety() - KOOPA_BBOX_HEIGHT / 2;
			//ay = 0;
			isOnTop = 1;
			return;
		}

	}
}
void CKOOPA::SetState(int state){
	if (state == 0) {
		this->state = LIFE;
	}
	else if (state == 1) {
		this->state = MAI;
	}
	else if (state == 2) {
		this->state = MAI_MOVE;
	}
	else if (state == 3) {
		this->state = DIE;
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
	}
}
void CKOOPA::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - KOOPA_BBOX_WIDTH / 2;
	t = y - KOOPA_BBOX_HEIGHT / 2;
	r = l + KOOPA_BBOX_WIDTH;
	b = t + KOOPA_BBOX_HEIGHT;
}