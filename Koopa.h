#pragma once
#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 25
#define KOOPA_BBOX_HEIGHT_DIE 7

#define KOOPA_DIE_TIMEOUT 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_DIE 200

#define ID_ANI_KOOPA_WALKING 5000
#define ID_ANI_KOOPA_DIE 5001
enum KoopaState {
	LIFE,
	MAI,
	MAI_MOVE,
	DIE
};
class CKOOPA : public CGameObject
{
protected:
	float ax;
	float ay;
	KoopaState state;
	ULONGLONG die_start;
	float roiy1 = -1, roiy2 = -1;
	int isOnTop = 0;
	int isroi = 1;
public:
	CKOOPA(float x, float y) :CGameObject(x, y) {
		state = LIFE;
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		vx = -KOOPA_WALKING_SPEED;
		die_start = -1;
		this->SetType(OBJECT_TYPE_KOOPA);
	}
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};