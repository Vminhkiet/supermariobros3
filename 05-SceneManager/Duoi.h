#pragma once
#include "GameObject.h"
#define Duoi_WIDTH 10
#define Duoi_HEIGHT 5
#define Duoi_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
class Duoi : public CGameObject {
	bool roi = false;
	bool doituong = false;
	float ay;
	float ax;
	int nx;
	ULONGLONG Isroi;
	int count = -1;
public:
	Duoi(float x, float y,int nx) :CGameObject(x, y) {
		ay = 0;
		this->nx = nx;
		if (nx < 0) {
			ax = -0.0015f;
		}
		else {
			ax = 0.0015f;
		}
		Isroi = -1;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsCollidable() {
		return 1;
	};
	void OnNoCollision(DWORD dt);
	int isBlocking() {
		return 0;
	}
};