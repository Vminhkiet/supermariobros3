#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_CURTAIN 12000


#define CURTAIN_SPEED 1

class CCurtain : public CGameObject {
	bool stop = false;
public:
	CCurtain(float x, float y) : CGameObject(x, y) {}
	void Setstop(bool b) {
		stop = b;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};