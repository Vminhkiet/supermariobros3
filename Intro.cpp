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

	three = new CThree(155,120);
	this->objects.push_back(three);

	leaf = new CLEAF(153, 20);
	this->objects.push_back(leaf);
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
		
		three->setdraw(true);
		mariored->SetSittingFalse();
		draw = true;
	}

}
void Intro::EndIntro() {
	if (draw) {
	//background
	D3DXCOLOR color(255.0f / 255.0f, 216.0f / 255.0f, 154.0f / 255.0f, 1.0f);
	CGame::GetInstance()->SetBackgroundColor(color);

	leaf->setdraw(true);
    }
	//tree

	CSprites::GetInstance()->Get(60003)->Draw(30, 135, 64, 70);
	CSprites::GetInstance()->Get(60004)->Draw(276, 120, 64, 100);
	//title

	CSprites::GetInstance()->Get(60005)->Draw(150, 60, 150, 80);
    //player
	//CSprites::GetInstance()->Get(60006)->Draw(, 80, -1, -1);
	//CSprites::GetInstance()->Get(60007)->Draw(600, 80, -1, -1);
	//smoke
	CSprites::GetInstance()->Get(60008)->Draw(50, 40, 30, 30);
	CSprites::GetInstance()->Get(60008)->Draw(240, 40, 30, 30);
	CSprites::GetInstance()->Get(60009)->Draw(40, 80, 15, 15);
	//CSprites::GetInstance()->Get(60010)->Draw(600 80, -1, -1);
	//CSprites::GetInstance()->Get(60011)->Draw(600, 80, -1, -1);
	//CSprites::GetInstance()->Get(60012)->Draw(600, 80, -1, -1);

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
	
	if (draw) {
		EndIntro();
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			objects[i]->Render();
	}
	
}
