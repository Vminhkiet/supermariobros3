#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Duoi.h"
#include "PlayScene.h"
#include "debug.h"
#include "AssetIDs.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_ROICHAM			800
#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_FLY				700
#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON		3
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_RACOON_BBOX_WIDTH  17
#define MARIO_RACOON_BBOX_HEIGHT 26
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500


#define SPEED_INTRO 1

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	bool cammai = false;
	int level;
	int untouchable;
	bool draw = false;
	ULONGLONG untouchable_start;
	ULONGLONG st;
	ULONGLONG sdanh;
	ULONGLONG roicham1;
	BOOLEAN isfly;
	BOOLEAN isOnPlatform;
	LPGAMEOBJECT duoi;
	string name;
	bool dangdichuyen = false;
	int len = 0;
	float vitri = 0;
	bool tele = false;
	bool dichchuyen = false;
	bool down = false;
	bool cground = true;
	bool up = false;
	bool change = false;
	bool danh = false;
	bool duocphep = true;
	bool l = false;
	bool r = true;
	bool t = false;
	bool b = false;
	string vitri1 = "1";
	int coin;
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
	void OnCollisionWithDie(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithSwap(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionblock(LPCOLLISIONEVENT e);
	void OnCollisionWithTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPara(LPCOLLISIONEVENT e);
	void OnCollisionWithFinish(LPCOLLISIONEVENT e);
	void OnCollisionWithParakoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithKick(LPCOLLISIONEVENT e);
	void OnCollisionWithNODE(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();
	void TailUpdate();
	bool mariogreen = false;
	int isroi = 0;
	int isOnTop = 0;
	float roiy1 = -1, roiy2 = -1;
	float ytop = -1;
	int kichhoat = 1;
	int intro = 1;
	bool dung = false;
	bool dacam = false;
	bool hoalon = false;
	bool battu = false;
	bool nhapnhay = false;
	bool fly = false;
	bool roicham = false;
	bool dangcam = false;
	int id = -1;
	int idphong = -1;
public:
	CMario(float x, float y, int intro = 1, bool mariogreen = false) : CGameObject(x, y)
	{
		sdanh = 0;
		this->mariogreen = mariogreen;
		this->intro = intro;
		isSitting = false;
		isfly = 0;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		st = -1;
		roicham1 = 0;
		duoi = NULL;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		this->SetType(OBJECT_TYPE_MARIO);
	}
	int getidphong() {
		return idphong;
	}
	int getintro();
	bool gettele() {
		return tele;
	}
	bool getduocphep() {
		return duocphep;
	}
	void setduocphep(bool duocphep) {
		this->duocphep = duocphep;
	}
	void SetSittingFalse() {
		isSitting = false;
	}
	bool getdangcam() {
		return dangcam;
	}
	void gethuongdi(bool& l, bool& r, bool& t, bool& b) {
		l = this->l;
		r = this->r;
		t = this->t;
		b = this->b;
	}
	void setdangcam(bool dangcam) {
		this->dangcam = dangcam;
	}
	void Setcam(bool cammai) {
		this->cammai = cammai;
		if (!cammai) {
			this->dacam = cammai;
			dangcam = false;
		}

	}
	void setid(int id) {
		this->id = id;
	}
	void setay() {
		ay = 0;
		vy = 0;
		vx = 0;
		ax = 0;
	}
	int getdraw() {
		return nx;
	}
	bool getcam() {
		return this->cammai;
	}
	void SetAXY(float ax, float ay) { this->ax = ax; this->ay = ay; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void Vacham();
	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}
	void setroicham() {
		roicham1 = GetTickCount64();
		vy = 0;
	}
	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int Getlevel() {
		return level;
	}
	void SetDanh(bool danh);
	bool checkfly() {
		return fly;
	}
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};