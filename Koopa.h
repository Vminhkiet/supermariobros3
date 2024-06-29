#pragma once
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
enum KoopaState {
	LIFE,
	MAI,
	MAI_MOVE,
	DIE1
};
class CKOOPA : public CGameObject
{
protected:
	float ax;
	float ay;
	KoopaState state;
	Thebox* box;
	bool danghoisinh = false;
	ULONGLONG hoisinh;
	ULONGLONG stop;
	ULONGLONG dung;
	ULONGLONG die_start;
	ULONGLONG timeroi;
	float roiy1 = -1, roiy2 = -1;
	int isOnTop = 0;
	int isroi = 1;
	bool huongdichuyen = false;
	bool bicam = false;
	bool green = false;
public:
	CKOOPA(float x, float y, bool green = false) :CGameObject(x, y) {
		state = LIFE;
		stop = 0;
		hoisinh = 0;
		this->ax = 0;
		this->green = green;
		this->ay = KOOPA_GRAVITY;
		vx = -KOOPA_WALKING_SPEED;
		timeroi = -1;
		die_start = -1;
		this->SetType(OBJECT_TYPE_KOOPA);
		box = new Thebox(x - 8, y);
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		currentScene->AddObject(box);
	}
	void SetState(int state);
	int Getstate() {
		if (state == LIFE)
			return 0;
		else if (state == MAI)
			return 1;
		else if (state == MAI_MOVE)
			return 2;
		else
			return 3;
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

	virtual int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};