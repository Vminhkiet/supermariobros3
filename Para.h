#pragma once
#include "GameObject.h"

#define PARA_GRAVITY 0.0005f
#define PARA_WALKING_SPEED 0.05f

#define PARA_JUMP_SPEED_Y	0.32f
#define PARA_JUMP_SPEED_Y_SHORT	0.12f

#define PARA_BBOX_WIDTH 16
#define PARA_BBOX_HEIGHT 14
#define PARA_BBOX_HEIGHT_DIE 7

#define PARA_DIE_TIMEOUT 500

#define PARA_STATE_WALKING 100
#define PARA_STATE_DIE 200
#define PARA_STATE_JUMP 300
#define PARA_STATE_JUMP_SHORT 400
#define PARA_STATE_RELEASE_JUMP	301

#define ID_ANI_PARA_WALKING 5006
#define ID_ANI_PARA_DIE 5005
#define ID_ANI_PARA_DIEKOOPA 5004
class CPARA : public CGameObject
{
protected:
	float ax;
	float ay;
	int level = 1;
	bool rua = false;
	bool canh = true;
	ULONGLONG die_start;
	ULONGLONG startjump;
	BOOLEAN isOnPlatform;
	BOOLEAN jump;
	BOOLEAN walk;
	int jumpshort = 2;
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