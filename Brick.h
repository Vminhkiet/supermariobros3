#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
	bool die = false;
	bool p = false;
	bool bat = false;
	ULONGLONG isdie;
public:
	CBrick(float x, float y, bool p) : CGameObject(x, y) { this->SetType(OBJECT_TYPE_BRICK); this->p = p; isdie = -1; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool getp() {
		return p;
	}
	void setdie(bool die) {
		this->die = die;
		isdie = GetTickCount64();
	}
	void setbat(bool bat) {
		this->bat = bat;
	}
};