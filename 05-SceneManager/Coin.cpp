#include "Coin.h"
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (ques) {
		if (ycu != y + 50) {
			y -= 2;
		}
		else {
			dungve = true;
			this->Delete();
		}
	}
	CGameObject::Update(dt, coObjects);
}
void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(!dungve)
	   animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}