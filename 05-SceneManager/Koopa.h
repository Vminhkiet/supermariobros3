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
	bool res = false;
	bool die = false;
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
	bool cho = false;
	bool huongdichuyen = false;
	bool bicam = false;
	bool lat = false;
	bool green = false;
	bool nhay = false;
	float startx, starty;
	bool draw = true;
public:
	CKOOPA(float x, float y, bool green = false) :CGameObject(x, y) {
		state = LIFE;
		stop = 0;
		startx = x;
		starty = y;
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
	void getisOnTop() {

		if (isOnTop)
			y += 5;
	}
	void getstart(float& startx, float& starty) {
		startx = this->startx;
		starty = this->starty;
	}
	bool getdie() {
		return die;
	}
	void setcam(bool cam) {
		this->bicam = cam;
	}
	void setres(bool res) {
		this->res = res;
	}
	bool getres() {
		return res;
	}
	void sethuong(bool huong) {
		huongdichuyen = huong;
	}
	void setdraw(bool draw) {
		this->draw = draw;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();

	virtual int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};