#include "Para.h"
#include "AssetIDs.h"
#include "Koopa.h"
#include "Ground.h"
#include "PlayScene.h"
#include "Mario.h"
CPARA::CPARA(float x, float y) :CGameObject(x, y)
{
	walk = true;
	this->ax = 0;
	this->ay = PARA_GRAVITY;
	die_start = -1;
	SetState(PARA_STATE_WALKING);
	ycu = y;
	isOnPlatform = false;
	this->SetType(OBJECT_TYPE_PARA);
	startjump = -1;
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
	if (x - mx > 50) {
		if (vx > 0) {
			vx *= -1;
		}
	}
	else if (mx - x > 50) {
		if (vx < 0) {
			vx *= -1;
		}
	}
	
	if (isOnPlatform) {
		jump = false;
	}
	else jump = true;
	if (vy < 0 && jump) {
		vy += (ay + 0.0001f) * (dt);
	}
	if (!jump) {
		if (GetTickCount64() - startjump < 2000) {
			walk = true;
		}
		else if (isOnPlatform && jumpshort > 0 ) {
			SetState(PARA_STATE_JUMP_SHORT);
			jumpshort--;
		}
		else if (isOnPlatform && jumpshort == 0) {
			SetState(PARA_STATE_JUMP);
			startjump = GetTickCount64();
			
		}
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
	else if (jump) {
		aniId = 5008;
	}
	if (walk) {
		aniId = ID_ANI_PARA_WALKING;
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
		if (isOnPlatform)
		{	
			vy = -PARA_JUMP_SPEED_Y;
			jumpshort = 2;
		}
		break;
	case PARA_STATE_JUMP_SHORT://;
		if (isOnPlatform)
		{
			jump = true;
			walk = false;
			vy = -PARA_JUMP_SPEED_Y_SHORT;

		}
		break;
	}
}
