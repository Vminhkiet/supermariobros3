#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"
#include "AssetIDs.h"
#include "debug.h"

class CTop : public CGameObject {
	float height;
	float width;

public:
	CTop(float x, float y, float width, float height) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		this->SetType(OBJECT_TYPE_TOP);
	}
	int IsBlocking() {
		return 0;
	}
	float getwidth() {
		return width;
	}
	float getx() {
		return x;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};