#pragma once
#include "GameObject.h"
class NODE :public CGameObject
{

	string name;
	int id = -1;
	bool diduoc = false;
	bool l = false;
	bool r = false;
	bool t = false;
	bool b = false;
public:
	NODE(float x, float y,string name) :CGameObject(x, y) {
		this->name = name;
		if (name == "1" || name=="2" || name=="3" || name=="10" || name == "5" || name == "19" || name == "21" || name == "22" || name == "7" || name == "8" || name == "12" || name == "14" || name == "16" || name == "18") {
			diduoc = true;
		}
		if (name == "1") {
			r = true;
		}
		else if (name == "2") {
			l = true;
			t = true;
		}
		else if (name == "3") {
			b = true;
		}
		if (name == "3") {
			id = 2;
		}
	}
	int getid() {
		return id;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void setdiduoc(bool diduoc) {
		this->diduoc = diduoc;
	}
	void gethuong(bool& l, bool& r, bool& t, bool& b) {
		l = this->l;
		r = this->r;
		t = this->t;
		b = this->b;
	}
	bool getdiduoc() {
		return diduoc;
	}
	string getname() {
		return name;
	}
	virtual int IsCollidable() {
		return 1;
	};
};


