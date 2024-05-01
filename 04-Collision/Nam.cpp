#include "NAM.h"

void CNAM::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_NAM)->Render(x, y);

	RenderBoundingBox();
}

void CNAM::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - NAM_BBOX_WIDTH / 2;
	t = y - NAM_BBOX_HEIGHT / 2;
	r = l + NAM_BBOX_WIDTH;
	b = t + NAM_BBOX_HEIGHT;
}
void CNAM::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == NAM_STATE_DIE) && (GetTickCount64() - die_start > NAM_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CNAM::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case NAM_STATE_DIE:
		die_start = GetTickCount64();
		y += (NAM_BBOX_HEIGHT - NAM_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case NAM_STATE_WALKING:
		vx = -NAM_WALKING_SPEED;
		break;
	}
}
void CNAM::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CNAM::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CNAM*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
