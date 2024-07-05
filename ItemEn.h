#pragma once
#include "GameObject.h"
class ItemEn:public CGameObject
{
	bool doi = false;
	ULONGLONG tg;
public:
	ItemEn(float x, float y) :CGameObject(x, y) {
		vx = 0.008;
		tg = -1;
	}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
};

