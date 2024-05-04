#include "MUSHROOM.h"

void CMUSHROOM::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (red)
		animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
	else
		animations->Get(ID_ANI_MUSHROOM + 1)->Render(x, y);
	RenderBoundingBox();
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
		vx = -MUSHROOM_WALKING_SPEED;
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
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMUSHROOM*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
