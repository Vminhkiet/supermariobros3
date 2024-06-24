#include "Swap.h"
void Swap::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x ;
	t = y;
	r = l + w;
	b = t + h;
}