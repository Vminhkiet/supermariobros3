#pragma once
#include "GameObject.h"
class Finish:public CGameObject
{
	int i = 0;
	float ax;
	float ay;
	bool dung = false;
	ULONGLONG die;
	ULONGLONG chuyen;
public:
	Finish(float x, float y) :CGameObject(x, y) {
		ax = 0;
		ay = 0;
		chuyen = 0;
	}
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	bool getdung() {
		return dung;
	}
	void Setdung(bool dung) {
		this->dung = dung;
		if (dung) {
			ay = 0.0002f;
			vy = -0.1f;
			die = GetTickCount64();
		}
	}
	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

