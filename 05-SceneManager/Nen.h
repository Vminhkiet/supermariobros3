#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Textures.h"
#include "AssetIDs.h"
#define ID_ANI_NEN 13000
#define NEN_WIDTH 480
#define NEN_BBOX_WIDTH 480
#define NEN_BBOX_HEIGHT 45

class CNEN : public CGameObject {

public:
	CNEN(float x, float y) : CGameObject(x, y) { this->SetType(OBJECT_TYPE_NEN); }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
typedef CNEN* LPNEN;