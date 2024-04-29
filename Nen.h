#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Textures.h"

#define ID_ANI_NEN 13000
#define NEN_WIDTH 480
#define NEN_BBOX_WIDTH 480
#define NEN_BBOX_HEIGHT 45

class CNEN : public CGameObject {
	float cellWidth;
public:
	CNEN(float x, float y, float width) : CGameObject(x, y) { cellWidth = width; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};
typedef CNEN* LPNEN;