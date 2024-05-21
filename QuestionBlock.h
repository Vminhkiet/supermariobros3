#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define ID_ANI_QUES 10001
#define QUES_WIDTH 16
#define QUES_BBOX_WIDTH 16
#define QUES_BBOX_HEIGHT 16

class CQuestionblock : public CGameObject {
	bool bicham = false;
public:
	CQuestionblock(float x, float y) : CGameObject(x, y) { 
		this->SetType(OBJECT_TYPE_QUES);
	}
	void SetCham(bool cham) { 
		bicham = cham;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
