#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Coin.h"
#include "Mushroom.h"
#include "ButtonP.h"
#include "Leaf.h"

#define ID_ANI_QUES 10001
#define QUES_WIDTH 17
#define QUES_BBOX_WIDTH 17
#define QUES_BBOX_HEIGHT 17
// power coin 1
//       nam  2
//       leaf 3
class CQuestionblock : public CGameObject {
	LPGAMEOBJECT obj = nullptr;
	bool bicham = false;
	int power = 0;
	float ycu;
	int cnt = 2;
	bool dathem = false;
	bool brick=false;
public:
	CQuestionblock(float x, float y, int power = 0, bool brick = false) : CGameObject(x, y) {
		this->SetType(OBJECT_TYPE_QUES);
		this->brick = brick;
		ycu = y;
		this->power = power;
		if (power == 1) {
			obj = new CCoin(x, y, true);
		}
		else if (power == 2) {
			if (!brick)
				obj = new CMUSHROOM(x, y, true, true);
			else
				obj = new CMUSHROOM(x, y, false, true);
		}
		else if (power == 3) {
			obj = new CLEAF(x, y);
		}
		else if (power == 4) {
			obj = new ButtonP(x, y - 16);
		}
	}
	void SetCham(bool cham) { 
		bicham = cham;
	}
	bool getcham() {
		return bicham;
	}
	int getpower() {
		return power;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
};
