#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "Thebox.h"
#include "Playscene.h"
#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 25
#define KOOPA_BBOX_HEIGHT_DIE 7
#define MAI_BBOX_WIDTH 16
#define MAI_BBOX_HEIGHT 16
#define KOOPA_DIE_TIMEOUT 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_DIE 200

#define ID_ANI_KOOPA_WALKING 5000
#define ID_ANI_KOOPA_DIE 5001
enum ParaKoopaState {
	LIFE2,
	MAI2,
	MAI_MOVE2,
	DIE2
};
class CParaKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	ParaKoopaState state;
	ULONGLONG die_start;
	ULONGLONG dung;
	BOOLEAN jump;
	BOOLEAN isOnPlatform;
	float roiy1 = -1, roiy2 = -1;
	int isOnTop = 0;
	int isroi = 1;
	bool huongdichuyen = false;
	bool bicam = false;
	bool green = true;
	bool canh = true;
public:
	CParaKoopa(float x, float y, bool green = true) :CGameObject(x, y) {
		state = LIFE2;
		this->ax = 0;
		this->green = green;
		this->ay = KOOPA_GRAVITY;
		vx = -KOOPA_WALKING_SPEED;
		die_start = -1;
		this->SetType(OBJECT_TYPE_KOOPA);
	}
	void SetState(int state);
	int Getstate() {
		if (state == LIFE2)
			return 0;
		else if (state == MAI2)
			return 1;
		else if (state == MAI_MOVE2)
			return 2;
		else
			return 3;
	}
	void setcanh(bool canh) {
		this->canh = canh;
	}
	bool getcanh() {
		return canh;
	}
	void setcam(bool cam) {
		this->bicam = cam;
	}
	void sethuong(bool huong) {
		huongdichuyen = huong;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};