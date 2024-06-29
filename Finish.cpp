#include "Finish.h"

void Finish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	if (GetTickCount64()-die>500 && !this->IsDeleted() && dung) {
		this->Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void Finish::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (!dung && GetTickCount64()-chuyen> 200) {
		i++;
		if (i > 3) {
			i = 0;
		}
		chuyen = GetTickCount64();
	}
	if (i==0)
		animations->Get(9994)->Render(x, y);
	else if(i==1)
		animations->Get(9995)->Render(x, y);
	else if(i==2)
		animations->Get(9996)->Render(x, y);

	//RenderBoundingBox();
}
void Finish::OnNoCollision(DWORD dt) {
	y += vy * dt;
}
void Finish::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = x - 18 / 2;
	t = y - 18 / 2;
	r = l + 18;
	b = t + 18;
}