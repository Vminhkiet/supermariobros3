#include "Grass.h"

void Grass::Render() {
	CAnimations::GetInstance()->Get(13012)->Render(x, y);
}
void Grass::GetBoundingBox(float& l, float& t, float& r, float& b){
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l + 16;
	b = t + 16;
}