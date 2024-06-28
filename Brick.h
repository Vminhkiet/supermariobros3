#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 17
#define BRICK_BBOX_WIDTH 17
#define BRICK_BBOX_HEIGHT 17

class CBrick : public CGameObject {
	bool die = false;
	ULONGLONG isdie;
public:
	CBrick(float x, float y) : CGameObject(x, y) { 
		this->SetType(OBJECT_TYPE_BRICK); isdie = -1;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool gettien() {
		if (die) {
			return true;
		}
		return false;
	}
	int IsBlocking() {
		if (die)
			return 0;
		return 1;
	}
	void settien(bool te);
	void setdie(bool die) {
		this->die = die;
		isdie = GetTickCount64();
	}
};