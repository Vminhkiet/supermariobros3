#include "Grass.h"

void Grass::Render() {
	CAnimations::GetInstance()->Get(13012)->Render(x, y);
}
void Grass::GetBoundingBox(float& l, float& t, float& r, float& b){
	l = x - 48 / 2;
	t = y - 48 / 2;
	r = l + 48;
	b = t + 48;
}