#include "Ground.h"


void CGround::Render() {
	RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + height;
}