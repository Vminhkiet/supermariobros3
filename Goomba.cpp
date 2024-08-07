#include "Goomba.h"
#include "AssetIDs.h"
#include "Koopa.h"
#include "Ground.h"
CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
	this->SetType(OBJECT_TYPE_GOOMBA);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x -= vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<Thebox*>(e->obj)) {
		rua = true;
		SetState(GOOMBA_STATE_DIE);
		return;
	}
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 
	if (dynamic_cast<CKOOPA*>(e->obj)) {
		CKOOPA* obj = dynamic_cast<CKOOPA*>(e->obj);
		if (obj->Getstate() == 2) {
			rua = true;
			SetState(GOOMBA_STATE_DIE);
			return;
		}
	}
	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CGround*>(e->obj) && e->nx == 0) {
		CGround* gr = dynamic_cast<CGround*>(e->obj);
		
		float tx, ty;
		gr->GetPosition(tx, ty);
		ty = gr->getwidth();
		yroi1 = tx;
		yroi2 = ty + tx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (!draw) {
		this->ay = GOOMBA_GRAVITY/20;
		vx = 0;
		ax = 0;
		vy = 0;
		return;
	}
	if (vx!=0 && (x<yroi1 || x>yroi2 )) {
		if (x < yroi1)
			x++;
		else if (x > yroi2)
			x--;
		vx *= -1;
		
	}
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	if (!draw)
		return;
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE) 
	{
		if (!rua)
			aniId = ID_ANI_GOOMBA_DIE;
		else
			aniId = ID_ANI_GOOMBA_DIEKOOPA;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
	}
}
