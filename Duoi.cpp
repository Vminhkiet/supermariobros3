#include "Duoi.h"
#include"QuestionBlock.h"
#include"Goomba.h"
#include"Venus.h"
#include"Brick.h"
#include"Para.h"
#include"Koopa.h"
#include "ParaKoopa.h"
#include "Brick.h"
#include "PlayScene.h"
#include "Mario.h"

void Duoi::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void Duoi::Render() {

	RenderBoundingBox();
}
void Duoi::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - Duoi_WIDTH / 2;
	t = y - Duoi_HEIGHT / 2;
	r = l + Duoi_WIDTH;
	b = t + Duoi_HEIGHT;
}
void Duoi::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMario*>(e->obj))
		return;
	if (dynamic_cast<CBrick*>(e->obj))
		dynamic_cast<CBrick*>(e->obj)->setdie(true);
	else if (dynamic_cast<CQuestionblock*>(e->obj))
		dynamic_cast<CQuestionblock*>(e->obj)->SetCham(true);
	else if (dynamic_cast<CKOOPA*>(e->obj))
		dynamic_cast<CKOOPA*>(e->obj)->SetState(3);
	else if (dynamic_cast<CVenus*>(e->obj)) {
		if (dynamic_cast<CVenus*>(e->obj)->getdie()) {
			return;
		}
		dynamic_cast<CVenus*>(e->obj)->setdie(true);
	}
	else if (dynamic_cast<CGoomba*>(e->obj)) {
		dynamic_cast<CPARA*>(e->obj)->Setrua(true);
		dynamic_cast<CGoomba*>(e->obj)->SetState(200);
	}
	else if (dynamic_cast<CPARA*>(e->obj)) {
		dynamic_cast<CPARA*>(e->obj)->Setrua(true);
		dynamic_cast<CPARA*>(e->obj)->SetState(200);
	}
	else if (dynamic_cast<CParaKoopa*>(e->obj)) {
		dynamic_cast<CParaKoopa*>(e->obj)->setcanh(false);
		dynamic_cast<CParaKoopa*>(e->obj)->SetState(3);
	}
}
void Duoi::OnNoCollision(DWORD dt) {
	//x +=vx*dt;
	y += vy * dt;
}