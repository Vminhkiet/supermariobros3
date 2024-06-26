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
			if (power == 0) {
				CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
				int level = mario->Getlevel();
				if (level == 1) {
					if (!brick)
						obj = new CMUSHROOM(x, y, true, true);
					else
						obj = new CMUSHROOM(x, y, false, true);
				}
				else
					obj = new CLEAF(x, y);
			}
			currentScene->AddObject(obj,this);
			dathem = true;
		}
	}
	
	
}

void CQuestionblock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (!bicham) {
		if (brick) {
			animations->Get(ID_ANI_QUES-1)->Render(x, y);
		}
		else animations->Get(ID_ANI_QUES)->Render(x, y, 18, 18);
	}
	else {
		animations->Get(ID_ANI_QUES + 1)->Render(x, y, 18, 18);
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
