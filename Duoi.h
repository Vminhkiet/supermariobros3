#pragma once
#include"GameObject.h"
#define THEBOX_WIDTH 10
#define THEBOX_HEIGHT 5
/*class Duoi :public CGameObject
{
public:
	/*void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithPara(LPCOLLISIONEVENT e);
	void OnCollisionWithParaKoopa(LPCOLLISIONEVENT e);*/
	
	Duoi(float x, float y) :CGameObject(x, y) {

	}
	//void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsCollidable() {
		return 1;
	};
	int isBlocking() {
		return 0;
	}
};
*/
