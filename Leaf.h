#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF 13002
#define LEAF_WALKING_SPEED 0.05f
#define LEAF_GRAVITY 0.002f
#define LEAF_DIE_TIMEOUT 5000
#define LEAF_BBOX_HEIGHT_DIE 7
#define LEAF_STATE_WALKING 100
#define LEAF_STATE_DIE 200
#define	LEAF_WIDTH 10
#define LEAF_BBOX_WIDTH 10
#define LEAF_BBOX_HEIGHT 16
#define ID_ANI_LEAF_WALKING 6000
#define ID_ANI_LEAF_DIE 6001
class CLEAF : public CGameObject {
protected:
	float ax;
	float ay;
	float trucx;
	bool draw = false;
	DWORD startfalltime;
	ULONGLONG die_start;
public:
	CLEAF(float x, float y) : CGameObject(x, y) {
		startfalltime= GetTickCount64();
		this->ax = 0;
		this->ay = LEAF_GRAVITY;
		die_start = -1;
		SetState(LEAF_STATE_WALKING);
		trucx = x;
	}
	void setdraw(bool draw) { this->draw = draw; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
};