#pragma once
#include "Animations.h"
#include "GameObject.h"
class Grass:public CGameObject
{

public:
	Grass(float x, float y) :CGameObject(x, y) {

	}
	void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

