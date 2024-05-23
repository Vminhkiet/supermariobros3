#include "TopGround.h"


void CTop::Render() {
	//RenderBoundingBox();
}

void CTop::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + height;
}