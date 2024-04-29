#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_CURTAIN 12000


#define CURTAIN_SPEED 0.2

class CCurtain : public CGameObject {
public:
	CCurtain(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};