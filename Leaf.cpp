#include "LEAF.h"
#include "PlayScene.h"
#include "Mario.h"

void CLEAF::Render()
{
	if (draw) {
		
		CAnimations* animations = CAnimations::GetInstance();
		if (!doi) {
			animations->Get(ID_ANI_LEAF)->Render(x, y);
		}
		else {
			animations->Get(ID_ANI_LEAF+1)->Render(x, y);
		}
		//RenderBoundingBox();
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
		if (vy<0 ) {
			vy += (ay+0.0001f) * (dt);
		}


		if ((state == LEAF_STATE_DIE) && (GetTickCount64() - die_start > LEAF_DIE_TIMEOUT))
		{
			isDeleted = true;
			return;
		}
		vy += ay * dt;
		if (vy > 0 && !roi) {
			startfalltime = GetTickCount64();
			roi = true;
		}
		if (roi) {
			float time = (GetTickCount64() - startfalltime);
			x = trucx - amplitude * sin(frequency * time);
			float vantoc = -amplitude * frequency * cos(frequency * time);
			if (vantoc > 0) {
				doi = true;
			}
			else
				doi = false;
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
		
		break;
	}
}
void CLEAF::OnNoCollision(DWORD dt)
{

	y += vy * dt;
};

