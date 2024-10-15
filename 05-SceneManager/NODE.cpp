#include "NODE.h"
void NODE::Render() {
	if (name == "3") {
		CSprites::GetInstance()->Get(80009)->Draw(x, y, 16, 15);
	}
	else if (name == "1") {
		CSprites::GetInstance()->Get(80013)->Draw(x, y, 16, 17);
	}
	else if (name == "5") {
		CSprites::GetInstance()->Get(80010)->Draw(x, y, 16, 15);
	}
	else if (name == "19") {
		CSprites::GetInstance()->Get(80011)->Draw(x, y, 16, 15);
	}
	else if (name == "22") {
		CSprites::GetInstance()->Get(80012)->Draw(x, y, 16, 15);
	}
	else if (name == "12") {
		CSprites::GetInstance()->Get(80017)->Draw(x, y, 16, 15);
	}
	else if (name == "14") {
		CSprites::GetInstance()->Get(80018)->Draw(x, y, 16, 15);
	}
	else if (name == "7") {
		CSprites::GetInstance()->Get(80016)->Draw(x, y, 16, 15);
	}
	//RenderBoundingBox();
}
void NODE::GetBoundingBox(float& l, float& t, float& r, float& b) {
	if (diduoc) {
		l = x - 2 / 2;
		t = y - 2 / 2;
		r = l + 2;
		b = t + 2;
	}
	else {
		l = x - 48 / 2;
		t = y - 48 / 2;
		r = l + 48;
		b = t + 48;
	}
}