#include "QuestionBlock.h"

void CQuestionblock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (bicham) {
		y-=20;
		bicham = false;
	}
	CGameObject::Update(dt, coObjects);
}

void CQuestionblock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_QUES)->Render(x, y,16,16);
	//RenderBoundingBox();
}

void CQuestionblock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUES_BBOX_WIDTH / 2;
	t = y - QUES_BBOX_HEIGHT / 2;
	r = l + QUES_BBOX_WIDTH;
	b = t + QUES_BBOX_HEIGHT;
}