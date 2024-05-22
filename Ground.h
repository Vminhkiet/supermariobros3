#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"


class CGround : public CGameObject {
	float height;
	float width;
public:
	CGround(float x, float y, float width, float height) : CGameObject(x, y) { 
		this->width = width; 
		this->height = height; 
		this->SetType(OBJECT_TYPE_GROUND);
	}
	int IsBlocking() 
	{
		// Ch?n khi va ch?m t? m?i h??ng
		return 1;
	}
	void Render();
	void Update(DWORD dt){}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};