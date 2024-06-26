#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"


class CDie : public CGameObject {
	float height;
	float width;

public:
	CDie(float x, float y, float width, float height) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		this->SetType(OBJECT_TYPE_GROUND);
	}
	int IsBlocking()
	{
		return 1;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	float getwidth() {
		return width;
	}
};