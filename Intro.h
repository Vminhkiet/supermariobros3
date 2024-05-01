#pragma once
#include "Curtain.h"
#include "Nen.h"
#include "Mario.h"
#include "Three.h"
class Intro {

	static Intro* __instance;
	int introTime;
	ULONGLONG introTimeStart;
	CCurtain* cur;
	CMario* mariored;
	CMario* mariogreen;
	CNEN* nen;
	CThree* three;
	vector<CGameObject*> objects;
	bool greenjump=false;
	bool draw = false;

public:
	static Intro* GetInstance();
	void Setitem(vector<LPGAMEOBJECT>& obj,LPGAMEOBJECT& player);
	void Update(DWORD dt);
	void Render();
	void PlanIntro();
	void EndIntro();
};