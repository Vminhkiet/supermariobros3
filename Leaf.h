#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define ID_ANI_LEAF 13010
#define LEAF_WALKING_SPEED 0.05f
#define LEAF_GRAVITY 0.00001f
#define LEAF_DIE_TIMEOUT 5000
#define LEAF_BBOX_HEIGHT_DIE 7
#define LEAF_STATE_WALKING 100
#define LEAF_STATE_DIE 200
#define	LEAF_WIDTH 10
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16
#define ID_ANI_LEAF_WALKING 6000
#define ID_ANI_LEAF_DIE 6001
class CLEAF : public CGameObject {
protected:
	float ax;
	float ay;
	float trucx;
	float ycu;
	bool draw = true;
	DWORD startfalltime;
	ULONGLONG die_start;
	bool roi = false;
	float angle; // Góc hiện tại của chiếc lá
	float angularVelocity; // Vận tốc góc
	float amplitude; // Biên độ dao động
	float frequency;
	bool doi = false;
	bool intro;
public:
	CLEAF(float x, float y, bool intro = false) : CGameObject(x, y) {
		startfalltime= GetTickCount64();
		this->ycu = y;
		this->ax = 0;
		this->intro = intro;
		this->trucx = x;
		this->ay = LEAF_GRAVITY;
		if(!intro)
		  this->vy = -0.12f;
		die_start = -1;
		SetState(LEAF_STATE_WALKING);
		trucx = x;
		this->SetType(OBJECT_TYPE_LEAF);
		this->angle = 0; // Bắt đầu từ góc 0
		this->angularVelocity = 0.0f; // Vận tốc góc ban đầu
		this->amplitude = 15; // Biên độ dao động
		this->frequency = 0.008f;
	}
	void setdraw(bool draw) { this->draw = draw; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	virtual int IsCollidable() { return 0; };
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);
};