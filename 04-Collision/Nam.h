#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_NAM 12000
#define NAM_WALKING_SPEED 0.05f
#define NAM_GRAVITY 0.002f
#define NAM_DIE_TIMEOUT 5000
#define NAM_BBOX_HEIGHT_DIE 7
#define NAM_STATE_WALKING 100
#define NAM_STATE_DIE 200
#define	NAM_WIDTH 10
#define NAM_BBOX_WIDTH 10
#define NAM_BBOX_HEIGHT 16
#define ID_ANI_NAM_WALKING 6000
#define ID_ANI_NAM_DIE 6001
class CNAM : public CGameObject {
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
public:
	CNAM(float x, float y) : CGameObject(x, y) {
		this->ax = 0;
		this->ay = NAM_GRAVITY;
		die_start = -1;
		SetState(NAM_STATE_WALKING);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
};