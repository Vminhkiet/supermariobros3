#include "Intro.h"

Intro* Intro::__instance = NULL;

Intro* Intro::GetInstance()
{
	if (__instance == NULL) __instance = new Intro();
	return __instance;
}

void Intro::Setitem(vector<LPGAMEOBJECT>& objects,LPGAMEOBJECT& player)
{
	introTimeStart = GetTickCount64();
	D3DXCOLOR blackColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	CGame::GetInstance()->SetBackgroundColor(blackColor);
	this->objects = objects;
	mariored = new CMario(10,150,0);
	mariored->SetLevel(MARIO_LEVEL_BIG);
	player = mariored;
	
	this->objects.push_back(mariored);

	mariogreen = new CMario(295,150,0,true);
	mariogreen->SetLevel(MARIO_LEVEL_BIG);
	mariogreen->SetState(200);
	mariogreen->SetState(0);
	this->objects.push_back(mariogreen);

	cur = new CCurtain(153,50);
	this->objects.push_back(cur);

	nen = new CNEN(153, 190);
	this->objects.push_back(nen);
	objects = this->objects;
}
void Intro::PlanIntro() {
	ULONGLONG timepassed = GetTickCount64() - introTimeStart;
	if (timepassed < 1000) {
		
	}
	else if (timepassed < 2000) {
		
		mariored->SetSpeed(200.0f, 0);
		mariogreen->SetSpeed(200.0f, 0);
		mariored->SetState(100);
		mariogreen->SetState(200);
	}
	else if (timepassed < 2800) {
		
		if (!greenjump) {
			greenjump = true;
			mariogreen->SetState(300);
			
		}
	}
	else if (timepassed < 5000) {
		
		mariored->SetSittingFalse();
	}
}
void Intro::Update(DWORD dt)
{
	PlanIntro();



	vector<CGameObject*> coObjects;

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			coObjects.push_back(objects[i]);
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			objects[i]->Update(dt, &coObjects);
	}
}

void Intro::Render()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			objects[i]->Render();
	}
	
	
}
