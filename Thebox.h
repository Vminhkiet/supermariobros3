#pragma once
#include "GameObject.h"
#define THEBOX_WIDTH 5
#define THEBOX_HEIGHT 5
#define THEBOX_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
class Thebox : public CGameObject {
	bool roi = false;
	bool doituong = false;
	float ay;
	float ax;
	ULONGLONG Isroi;
	int count = -1;
public:
	Thebox(float x, float y) :CGameObject(x, y) {
		ay = THEBOX_GRAVITY;
		ax = 0;
		Isroi = -1;
		vx = -KOOPA_WALKING_SPEED;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsCollidable() {
		return 1;
	};
	void OnNoCollision(DWORD dt);
	bool getroi() {
		return roi;
	}
	void setbandau() {
		roi = false;
		doituong = false;
		count = -1;
		vx *= -1;
		
	}
	void doihuong() {
		vx = -vx;
	}
	void setdoituong(bool dt) {
		doituong = dt;
	}
	int isBlocking() {
		return 0;
	}
};