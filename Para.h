#pragma once
#include "GameObject.h"

#define PARA_GRAVITY 0.002f
#define PARA_WALKING_SPEED 0.05f

#define PARA_JUMP_SPEED_Y	0.5f


#define PARA_BBOX_WIDTH 16
#define PARA_BBOX_HEIGHT 14
#define PARA_BBOX_HEIGHT_DIE 7

#define PARA_DIE_TIMEOUT 500

#define PARA_STATE_WALKING 100
#define PARA_STATE_DIE 200
#define PARA_STATE_JUMP 300
#define PARA_STATE_RELEASE_JUMP	301

#define ID_ANI_PARA_WALKING 5006
#define ID_ANI_PARA_DIE 5005
#define ID_ANI_PARA_DIEKOOPA 5004

class CPARA : public CGameObject
{
protected:
	float ax;
	float ay;
	bool rua = false;
	bool canh = true;
	ULONGLONG die_start;
	BOOLEAN isOnPlatform;
	float yroi1 = -1;
	float yroi2 = -1;
	float ycu;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPARA(float x, float y);
	virtual void SetState(int state);
};