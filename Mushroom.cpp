#include "MUSHROOM.h"
#include "TopGround.h"
#include "Bullet.h"
void CMUSHROOM::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (red)
		animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
	else
		animations->Get(ID_ANI_MUSHROOM + 1)->Render(x, y);
	//RenderBoundingBox();
}

void CMUSHROOM::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}
void CMUSHROOM::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (ques && !chamdinh) {
		y -=0.2;
		if (ycu > y + 18) {
			chamdinh = true;
			ay = MUSHROOM_GRAVITY;
			SetState(MUSHROOM_STATE_WALKING);
		}
	}
	if (roiy1 != -1 && roiy2 != -1) {
		if (x<roiy1 || x>roiy2) {
			roiy1 = -1;
			roiy2 = -1;
			isOnTop = 0;
		}
	}
	if (isOnTop) {
		isroi = 0;
	}
	if (!isOnTop)
	    vy += ay * dt;
	vx += ax * dt;

	if ((state == MUSHROOM_STATE_DIE) && (GetTickCount64() - die_start > MUSHROOM_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CMUSHROOM::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_DIE:
		die_start = GetTickCount64();
		y += (MUSHROOM_BBOX_HEIGHT - MUSHROOM_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case MUSHROOM_STATE_WALKING:
		float x, y;
		CGame::GetInstance()->GetCamPos(x, y);
		vx = -MUSHROOM_WALKING_SPEED;
		if (this->x > x)
			vx *= -1;
		break;
	}
}
void CMUSHROOM::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMUSHROOM::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBullet*>(e->obj)) return;
	if (!e->obj->IsBlocking() && e->obj->GetType()!=14) return;
	
	if (dynamic_cast<CMUSHROOM*>(e->obj)) return;
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

		if (isroi) {
			roiy1 = top->getx();
			roiy2 = roiy1 + top->getwidth();
			vy = 0;
			y = top->Gety() - MUSHROOM_BBOX_HEIGHT / 2;
			//ay = 0;
			isOnTop = 1;
			return;
		}

	}
}
