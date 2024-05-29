#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "Animation.h"
#include "Animations.h"

#define BULLET_SPEED 0.02f;

// 1:tren trai, 2:duoi trai, 3:tren phai, 4: tren trai
class CBullet:public CGameObject {
	int huong = 0;
public:
	CBullet(float x, float y, int huong):CGameObject(x,y) {
		this->huong = huong;
		vx = BULLET_SPEED;
		vx *= 2;
		vy = BULLET_SPEED;
		if (huong == 1) {
			vx *= -1;
			vy *= -1;
		}
		else if(huong==2){
			vx *= -1;
		}
		else if (huong == 3) {
			vy *= -1;
		}
		SetType(OBJECT_TYPE_BULLET);
	}
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
typedef CBullet* LPBULLET;