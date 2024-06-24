/*#include "Duoi.h"
#include"QuestionBlock.h"
#include"Goomba.h"
#include"Venus.h"
#include"Brick.h"
#include"Para.h"
#include"Koopa.h"

void Duoi::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}
void Render() {
	//RenderBoundingBox();
}
void Duoi::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - THEBOX_WIDTH / 2;
	t = y - THEBOX_HEIGHT / 2;
	r = l + THEBOX_WIDTH;
	b = t + THEBOX_HEIGHT;
}
/*void Duoi::OnCollisionWith(LPCOLLISIONEVENT e){
	if (dynamic_cast<CQuestionblock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CVenus*>(e->obj))
		OnCollisionWithVenus(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CKOOPA*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPARA*>(e->obj))
		OnCollisionWithPara(e);
}*/