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
	

	cur = new CCurtain(153,50);
	this->objects.push_back(cur);

	nen = new CNEN(153, 220);
	this->objects.push_back(nen);

	three = new CThree(155, 140);
	this->objects.push_back(three);

	leaf = new CLEAF(153, 0,true);
	leaf->setdraw(false);
	this->objects.push_back(leaf);

	mush = new CMUSHROOM(50, 10);
	mush->setdraw(false);
	this->objects.push_back(mush);

	gooba = new CGoomba(78, 10);
	gooba->SetSpeed(0, 0);
	gooba->setdraw(false);
	this->objects.push_back(gooba);

	koopa = new CKOOPA(153, -50,true);
	koopa->setdraw(false);
	this->objects.push_back(koopa);

	koopa1 = new CKOOPA(210, -50);
	koopa1->setdraw(false);
	this->objects.push_back(koopa1);

	mariored = new CMario(10, 150, 0);
	mariored->SetLevel(MARIO_LEVEL_BIG);
	player = mariored;

	this->objects.push_back(mariored);

	mariogreen = new CMario(295, 150, 0, true);
	mariogreen->SetLevel(MARIO_LEVEL_BIG);
	mariogreen->SetState(200);
	mariogreen->SetState(0);
	this->objects.push_back(mariogreen);
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
		
		greenjump = false;
		three->setdraw(true);
		mariored->SetSittingFalse();
		draw = true;
		
	}
	else if (timepassed < 6000) {
		mush->SetState(100);
	}
	else if (timepassed < 7500) {
		koopa->SetState(1);
		koopa1->SetState(1);
	}
	else if (timepassed < 7800) {
		koopa->SetState(1);
		koopa1->SetState(1);
		if (!greenjump) {
			greenjump = true;
			mariored->SetState(300);

		}
	}
	else if (timepassed < 7900) {
		greenjump = false;
	}
	else if (timepassed < 9000) {
		if (!greenjump) {
			greenjump = true;
			mariored->SetState(500);
			mariored->SetState(300);
		}
	}
	else if (timepassed < 10000) {
		mush->setdraw(false);
		mariored->SetState(100);
	}
	else {
		end = true;
	}
	
}
void Intro::EndIntro(int x) {
	if (draw) {
	//background
	D3DXCOLOR color(255.0f / 255.0f, 216.0f / 255.0f, 154.0f / 255.0f, 1.0f);
	CGame::GetInstance()->SetBackgroundColor(color);

	leaf->setdraw(true);
	mush->setdraw(true);
	gooba->setdraw(true);
	koopa->setdraw(true);
	koopa1->setdraw(true);

    }
	//tree

	CSprites::GetInstance()->Get(60003)->Draw(30, 165 + x, 64, 70);
	CSprites::GetInstance()->Get(60004)->Draw(276, 150 + x, 64, 100);
	//title

	CSprites::GetInstance()->Get(60005)->Draw(150, 75 + x, 150, 80);
    
	//smoke
	CSprites::GetInstance()->Get(60008)->Draw(50, 60 + x, 30, 30);
	CSprites::GetInstance()->Get(60008)->Draw(240, 60 + x, 30, 30);
	CSprites::GetInstance()->Get(60009)->Draw(40, 100 + x, 15, 15);

	if (end) {
		//player
		CSprites::GetInstance()->Get(60006)->Draw(150, 175, 105, 13);
		CSprites::GetInstance()->Get(60018)->Draw(90, 175, 8, 8);
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
	
	if (draw) {
		EndIntro(h);
		if(h<0)
		    h += 2;
	
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			objects[i]->Render();
	}
}
