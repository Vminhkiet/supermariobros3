#include "Brick.h"
void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (die && (GetTickCount64() - isdie > 300))
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(die)
		animations->Get(ID_ANI_BRICK - 2)->Render(x, y);
	else if(!bat)
	    animations->Get(ID_ANI_BRICK)->Render(x, y);
	else 
		animations->Get(ID_ANI_BRICK - 1)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}