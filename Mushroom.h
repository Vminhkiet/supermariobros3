#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#define ID_ANI_MUSHROOM 80000
#define MUSHROOM_WALKING_SPEED 0.05f
#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_DIE_TIMEOUT 5000
#define MUSHROOM_BBOX_HEIGHT_DIE 7
#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_DIE 200
#define	MUSHROOM_WIDTH 10
#define MUSHROOM_BBOX_WIDTH 10
#define MUSHROOM_BBOX_HEIGHT 16
#define ID_ANI_MUSHROOM_WALKING 6000
#define ID_ANI_MUSHROOM_DIE 6001
class CMUSHROOM : public CGameObject {
protected:
	float ax;
	float ay;
	bool red;
	ULONGLONG die_start;
public:
	CMUSHROOM(float x, float y,bool red=true) : CGameObject(x, y) {
		this->ax = 0;
		this->ay = MUSHROOM_GRAVITY;
		die_start = -1;
		this->red = red;
		SetState(MUSHROOM_STATE_WALKING);
		this->SetType(OBJECT_TYPE_NAM);
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