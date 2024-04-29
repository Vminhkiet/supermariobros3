#pragma once
#include "Curtain.h"
#include "debug.h"
void CCurtain::Update(DWORD dt) {
	y -= CURTAIN_SPEED * dt;
	DebugOut(L"y= \n", y);
	CGameObject::Update(dt);
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