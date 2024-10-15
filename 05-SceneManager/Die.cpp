#include "Die.h"

void CDie::Render() {
	// RenderBoundingBox();
}

void CDie::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + height;
}