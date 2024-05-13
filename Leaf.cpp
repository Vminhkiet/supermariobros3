#include "LEAF.h"

void CLEAF::Render()
{
	if (draw) {
		startfalltime = GetTickCount64();
		CAnimations* animations = CAnimations::GetInstance();

		animations->Get(ID_ANI_LEAF)->Render(x, y);
		RenderBoundingBox();
	}
}

void CLEAF::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}
void CLEAF::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (draw) {
		vy = ay*(dt);

		if ((state == LEAF_STATE_DIE) && (GetTickCount64() - die_start > LEAF_DIE_TIMEOUT))
		{
			isDeleted = true;
			return;
		}

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}
void CLEAF::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_DIE:
		die_start = GetTickCount64();
		y += (LEAF_BBOX_HEIGHT - LEAF_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case LEAF_STATE_WALKING:
		vx = -LEAF_WALKING_SPEED;
		break;
	}
}
void CLEAF::OnNoCollision(DWORD dt)
{

	y += vy * dt;
};

void CLEAF::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CLEAF*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}