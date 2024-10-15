#pragma once
#include "Curtain.h"
#include "debug.h"
void CCurtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (y+95 == 0) {
		Setstop(true);
		Render();
	}
	if (!stop) {
		y -= CURTAIN_SPEED;
	}
	CGameObject::Update(dt, coObjects);
}
void CCurtain::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(!stop)
	    animations->Get(ID_ANI_CURTAIN+14)->Render(x, y, 305, 240);
	else
		animations->Get(ID_ANI_CURTAIN + 15)->Render(x+10, y+105, 360, 20);
	//RenderBoundingBox();
}

void CCurtain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x;
	b = y;
}