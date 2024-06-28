#include "ButtonP.h"
void ButtonP::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void ButtonP::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (die)
		animations->Get(ID_ANI_BUTTONP - 3)->Render(x + 1, y + 5);
	else
		animations->Get(ID_ANI_BUTTONP - 1)->Render(x, y);

	//RenderBoundingBox();
}

void ButtonP::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BUTTONP_BBOX_WIDTH / 2;
	t = y - BUTTONP_BBOX_HEIGHT / 2;
	r = l + BUTTONP_BBOX_WIDTH;
	b = t + BUTTONP_BBOX_HEIGHT;
}