#include "HUD.h"

HUD* HUD::__instance = nullptr;
HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD(0,0);
	return __instance;
}
void HUD::Render() {

	CSprites::GetInstance()->Get(80050)->Draw(x, y, 314, 39);
	
}
void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
}
void HUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 2 / 2;
	t = y - 2 / 2;
	r = l + 2;
	b = t + 2;
}