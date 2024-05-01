#include "Nen.h"


void CNEN::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_NEN)->Render(x-10, y,390,45);
	//RenderBoundingBox();
}

void CNEN::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - NEN_BBOX_WIDTH / 2;
	t = y - NEN_BBOX_HEIGHT / 2;
	r = l + NEN_BBOX_WIDTH;
	b = t + NEN_BBOX_HEIGHT;
}