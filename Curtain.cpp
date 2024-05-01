#pragma once
#include "Curtain.h"
#include "debug.h"
void CCurtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	y -= CURTAIN_SPEED;
	CGameObject::Update(dt, coObjects);
}
void CCurtain::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CURTAIN)->Render(x, y,305,240);
	//RenderBoundingBox();
}

void CCurtain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x;
	b = y;
}