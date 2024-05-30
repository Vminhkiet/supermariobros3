#include "Para.h"
#include "AssetIDs.h"
#include "Koopa.h"
#include "Ground.h"
#include "PlayScene.h"
#include "Mario.h"
CPARA::CPARA(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PARA_GRAVITY;
	die_start = -1;
	SetState(PARA_STATE_WALKING);
	ycu = y;
	isOnPlatform = false;
	this->SetType(OBJECT_TYPE_PARA);
}

void CPARA::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARA_STATE_DIE)
	{
		left = x - PARA_BBOX_WIDTH / 2;
		top = y - PARA_BBOX_HEIGHT_DIE / 2;
		right = left + PARA_BBOX_WIDTH;
		bottom = top + PARA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARA_BBOX_WIDTH / 2;
		top = y - PARA_BBOX_HEIGHT / 2;
		right = left + PARA_BBOX_WIDTH;
		bottom = top + PARA_BBOX_HEIGHT;
	}
}

void CPARA::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPARA::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPARA*>(e->obj)) return;
	if (dynamic_cast<CKOOPA*>(e->obj)) {
		CKOOPA* obj = dynamic_cast<CKOOPA*>(e->obj);
		if (obj->Getstate() == 2) {
			rua = true;
			SetState(PARA_STATE_DIE);
			return;
		}
	}
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) {
			isOnPlatform = true;
		}
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CGround*>(e->obj)) {
		CGround* gr = dynamic_cast<CGround*>(e->obj);
		float tx, ty;
		gr->GetPosition(tx, ty);
		ty = gr->getwidth();
		yroi1 = tx;
		yroi2 = ty + tx;
	}
}

void CPARA::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x<yroi1 || x>yroi2) {
		if (x < yroi1)
			x++;
		else if (x > yroi2)
			x--;
		vx *= -1;

	}
	CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
	float mx, my;
	mario->GetPosition(mx, my);
	if (abs(mx - x) > 50 && isOnPlatform) {
		SetState(PARA_STATE_JUMP);
	}
	if (ycu < y + 50) {
		SetState(PARA_STATE_RELEASE_JUMP);
	}
	vy += ay * dt;
	vx += ax * dt;

	if ((state == PARA_STATE_DIE) && (GetTickCount64() - die_start > PARA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	isOnPlatform = false;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPARA::Render()
{
	int aniId = ID_ANI_PARA_WALKING;
	if (state == PARA_STATE_DIE)
	{
		if (!rua)
			aniId = ID_ANI_PARA_DIE;
		else
			aniId = ID_ANI_PARA_DIEKOOPA;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPARA::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARA_BBOX_HEIGHT - PARA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARA_STATE_WALKING:
		vx = -PARA_WALKING_SPEED;
		break;
	case PARA_STATE_JUMP:
		ay = 0;
		if (isOnPlatform)
		{	
			vy = -PARA_JUMP_SPEED_Y;
		}
		break;
	case PARA_STATE_RELEASE_JUMP:
		if (vy < 0) vy += PARA_JUMP_SPEED_Y / 2;

		break;
	}
}
