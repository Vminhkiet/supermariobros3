#include "QuestionBlock.h"
#include "Mario.h"
#include "PlayScene.h"
void CQuestionblock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	if (bicham) {
		if (cnt == 2)
			y--;
		if (cnt == 1)
			y++;
		if (y == ycu - 5) {
			cnt--;
		}
		if (y == ycu) {
			cnt--;
		}
		if (!dathem) {
			CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			currentScene->AddObject(obj,this);
			dathem = true;
		}
	}
	
	
}

void CQuestionblock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(!bicham)
	    animations->Get(ID_ANI_QUES)->Render(x, y,19,19);
	else {
		animations->Get(ID_ANI_QUES + 1)->Render(x, y, 19, 19);
	}
	//RenderBoundingBox();
}

void CQuestionblock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUES_BBOX_WIDTH / 2;
	t = y - QUES_BBOX_HEIGHT / 2;
	r = l + QUES_BBOX_WIDTH;
	b = t + QUES_BBOX_HEIGHT;
}
