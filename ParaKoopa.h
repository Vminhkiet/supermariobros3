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
	bool respawn = false;
	ULONGLONG timespawn;
	ParaKoopaState state;
	float startx, starty;
	bool danghoisinh = false;
	bool die = false;
	ULONGLONG bienmat;
	ULONGLONG hoisinh;
	ULONGLONG stop;
	ULONGLONG die_start;
	ULONGLONG dung;
	ULONGLONG dibo;
	BOOLEAN jump;
	BOOLEAN isOnPlatform;
	float roiy1 = -1, roiy2 = -1;
	int isOnTop = 0;
	int isroi = 1;
	bool huongdichuyen = false;
	bool bicam = false;
	bool green = true;
	bool res = false;
	bool nhay = false;
	bool lat = false;
	bool cho = false;
	bool canh = true;
public:
	CParaKoopa(float x, float y, bool green = true) :CGameObject(x, y) {
		state = LIFE2;
		this->ax = 0;
		stop = 0;
		hoisinh = 0;
		timespawn = 0;
		dibo = 0;
		startx = x;
		starty = y;
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
	bool getlat() {
		return lat;
	}
	void setlat(bool lat) {
		this->lat = lat;
		if (lat) {

			vy = -0.4f;
			nhay = true;
		}

	}
	bool getcho() {
		return cho;
	}
	bool getdie() {
		return die;
	}
	void setcanh(bool canh) {
		this->canh = canh;
	}
	void getstart(float& startx, float& starty) {
		startx = this->startx;
		starty = this->starty;
	}
	bool getres() {
		bienmat = GetTickCount64();
		return res;
	}
	void setres(bool res) {
		this->res = res;
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