#pragma once
#include"GameObject.h"
class Swap:public CGameObject
{
	bool start = false;
	float w, h;
	bool down = true;
	string name;
public:
	Swap(float x, float y, bool start = false, float w = 0, float h = 0, string name = "", bool down = true) :CGameObject(x, y) {
		this->start = start;
		this->w = w;
		this->h = h;
		this->down = down;
		this->name = name;
	}
	void Render(){ //RenderBoundingBox();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	bool getdown() {
		return down;
	}
	string getname() {
		if (name == "Swap1")
			return "C1";
		else if (name == "Swap2")
			return "C2";
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	virtual int IsCollidable() {
		return 1;
	};
};

