#include "Three.h"

void CThree::Render() {
	if (draw) {
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_THREE)->Render(x, y, 40, 40);
	}
}
void CThree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}