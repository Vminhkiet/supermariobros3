#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_THREE 12013


class CThree : public CGameObject {
	bool draw=false;
public:
	CThree(float x, float y) : CGameObject(x, y) {}
	void Render();
	void setdraw(bool draw) { this->draw = draw; }
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};