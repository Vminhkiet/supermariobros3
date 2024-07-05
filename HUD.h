#pragma once
#include "GameObject.h"
class HUD:public CGameObject
{
	static HUD* __instance;
	int mang = 4;
	int world = 1;
	int diem = 0;
	int tocdo = 0;
	bool p = false;
public:
	HUD(float x, float y) : CGameObject(x, y) {

	}
	static HUD* GetInstance();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 0; };
};

