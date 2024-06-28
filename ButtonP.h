#pragma once
#include"GameObject.h"
#define ID_ANI_BUTTONP 10000
#define BUTTONP_WIDTH 16
#define BUTTONP_BBOX_WIDTH 16
#define BUTTONP_BBOX_HEIGHT 16
class ButtonP:public CGameObject
{
	bool die = false;
public:
	ButtonP(float x, float y) : CGameObject(x, y) {  }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { 
		if (die)
			return 0;
		return 1;
	};
	bool getdie() {
		return die;
	}
	void setdie(bool die) {
		this->die = die;
	}
};

