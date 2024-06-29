#include "Koopa.h"
#include "TopGround.h"
#include "Mario.h"
#include "PlayScene.h"
#include "QuestionBlock.h"
#include "Brick.h"
#include "Ground.h"
#include "Die.h"
#include "Mario.h"
#include "Goomba.h"
#include "Para.h"
#include "ParaKoopa.h"
void CKOOPA::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (roiy1 != -1 && roiy2 != -1) {
		if (x<roiy1 || x>roiy2) {
			if (state != LIFE) {
				roiy1 = -1;
				roiy2 = -1;
				isOnTop = 0;
			}
			else {
				isOnTop = 1;
				vx *= -1;
				if (x < roiy1) {
					x++;
				}
				else if (x > roiy2) {
					x--;
				}
			}
		}
	}

	if (!box->IsDeleted()) {
		float cx, cy;
		box->GetSpeed(cx, cy);
		if (cx * vx < 0) {
			box->SetSpeed(vx, cy);
		}
	}
	if (GetTickCount64() - dung > 3000 && state == MAI_MOVE) {
		SetState(3);
	}
	if (state != LIFE && !box->IsDeleted()) {
		box->Delete();
	}
	if (isOnTop==1 && !box->IsDeleted()) {
		box->Delete();
	}
	if (box->getroi() && isOnTop == 0 && !box->IsDeleted()) {
		
		if (vx > 0) {
			box->SetPosition(x-2, y);
		}
		else
			box->SetPosition(x+2, y);
		vx *= -1;
		box->setbandau();
	}
	
	if (isOnTop) {
		isroi = 0;
	}
	if (!isOnTop)
	    vy += ay * dt;

	vx += ax * dt;
	if (state == MAI_MOVE) {
		if (huongdichuyen)
			vx = KOOPA_WALKING_SPEED * 6;
		else
			vx = -KOOPA_WALKING_SPEED * 6;
	}
	if ((state == DIE1) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CKOOPA::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == LIFE) {
		if (vx == 0)
		{
			if (nx > 0) {
				if (!green)
					aniId = 13007;
				else
					aniId = 13009;
			}
			else {
				if (!green)
					aniId = 13006;
				else
					aniId = 13008;
			}
		}
		else if (vx > 0)
		{
			if (!green)
				aniId = 13003;
			else
				aniId = 13011;
		}
		else // vx < 0
		{
			if (!green)
				aniId = 13002;
			else
				aniId = 13010;
		}
	}
	else if (state == MAI) {

		if (!green)
			aniId = 13004;
		else
			aniId = 13012;
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
		if (!mario->getcam() && bicam) {
			bicam = false;
			SetState(2);
			dung = GetTickCount64();
			float mx, my;
			mario->GetPosition(mx, my);
			if (isOnTop == 0) {
				y -= 5;
			}
			if (mx > x) {
				huongdichuyen = false;
			}
			else
				huongdichuyen = true;

		}
		if (bicam) {
			int draw = mario->getdraw();
			mario->GetPosition(x, y);
			if (draw>0)
				x += 8;
			else
				x -= 8;
		}
		if (GetTickCount64() - hoisinh >= 10000 && !danghoisinh) {
			danghoisinh = true;
			stop = GetTickCount64();
		}
		if (danghoisinh && GetTickCount64() - stop < 500) {
			if (!green)
				aniId = 13016;
			else
				aniId = 13017;
		}
	    if (danghoisinh && GetTickCount64() - stop > 500) {
			SetState(0);

		}
	}
	else if (state == MAI_MOVE) {
		if (!green)
			aniId = 13005;
		else
			aniId = 13013;
		
	}
	int w = 16;
	int h = 16;
	if (state == LIFE) {
		w = 16;
		h = 26;
	}
	if (state == DIE1)
		return;
	animations->Get(aniId)->Render(x, y,w,h);
}
void CKOOPA::OnNoCollision(DWORD dt)
{
	if (state != MAI) {
		x += vx * dt;
		y += vy * dt;
	}
};
void CKOOPA::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking() && e->obj->GetType() != 14 && e->obj->GetType()!=2 || e->obj->GetType()==16 ) return;
	if (dynamic_cast<Thebox*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) {
		CGoomba* gooba = dynamic_cast<CGoomba*>(e->obj);
		if(state==LIFE)
		   return;
		if (state == MAI_MOVE && gooba->GetState()==200) {
			return;
		}
	}
	if (dynamic_cast<CParaKoopa*>(e->obj) && state == MAI_MOVE) {
		dynamic_cast<CParaKoopa*>(e->obj)->SetState(3);
		return;
	}
	if (dynamic_cast<CPARA*>(e->obj) && state == MAI_MOVE) {
		dynamic_cast<CPARA*>(e->obj)->Setrua(true);
		dynamic_cast<CPARA*>(e->obj)->SetState(200);
	}
	if (dynamic_cast<CKOOPA*>(e->obj) && state == MAI_MOVE) {
		dynamic_cast<CKOOPA*>(e->obj)->SetState(3);
		return;
	}
	if (dynamic_cast<CMario*>(e->obj))
		return;
    if (dynamic_cast<CGoomba*>(e->obj)) {
		if (state == MAI_MOVE) {
			CGoomba* go = dynamic_cast<CGoomba*>(e->obj);
			go->Setrua(true);
			go->SetState(GOOMBA_STATE_DIE);
			vx *= -1;
		}
		return;
	}
	if (dynamic_cast<CKOOPA*>(e->obj)) return;
	
	if (e->obj->GetType() != 14) {
		
		if (e->ny != 0)
		{
			if(state==LIFE)
			    box->setdoituong(true);
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
			huongdichuyen = !huongdichuyen;
		}
	}

	if (dynamic_cast<CTop*>(e->obj)) {
		CTop* top = dynamic_cast<CTop*>(e->obj);
		if (e->ny < 0) {
			isroi = 1;
		}
		if (isroi) {
			roiy1 = top->getx();
			roiy2 = roiy1 + top->getwidth();
			vy = 0;
			box->setdoituong(true);
			y = top->Gety() - KOOPA_BBOX_HEIGHT / 2;
			//ay = 0;
			isOnTop = 1;
			return;
		}

	}
	else if (dynamic_cast<CGround*>(e->obj)) {
		if (box != NULL && !box->IsDeleted() && state == LIFE) {
			box->Delete();
		}
	}
	else if (dynamic_cast<CBrick*>(e->obj)) {
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		if (e->nx != 0 && state == MAI_MOVE) {
			brick->setdie(true);
			vx *= -1;
		}
	}
	else if (dynamic_cast<CDie*>(e->obj))
	{
		this->Delete();
	}
	else if (dynamic_cast<CQuestionblock*>(e->obj)) {
		CQuestionblock* qs = dynamic_cast<CQuestionblock*>(e->obj);
		if (e->nx != 0 && state == MAI_MOVE) {
			qs->SetCham(true);
			vx *= -1;
		}
	}
	
	
}
void CKOOPA::SetState(int state){
	if (state == 0) {
		
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
		if (mario->getcam()) {
			float cx, cy;
			mario->Vacham();
			mario->GetSpeed(cx, cy);
			mario->SetSpeed(cx, cy - 0.1f);
			mario->Setcam(false);
			
		}
		this->state = LIFE;
		y -= 5;
		danghoisinh = false;
		if (box->IsDeleted()) {
			if (vx < 0)
				box = new Thebox(x - 8, y );
			else
				box = new Thebox(x + 8, y );
			CPlayScene* k = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			k->AddObject(box);
		}
	
		if (nx < 0)
			vx = -KOOPA_WALKING_SPEED;
		else
			vx = KOOPA_WALKING_SPEED;
	}
	else if (state == 1) {
		this->state = MAI;
		vx = 0;
		if (bicam) {
			vy = 0;
		}
		if (isOnTop == 1) {
			y += 5;
		}
		hoisinh = GetTickCount64();
		
	}
	else if (state == 2) {
		dung = GetTickCount64();
		
		this->state = MAI_MOVE;
	}
	else if (state == 3) {
		this->state = DIE1;
		die_start = GetTickCount64();
		if (box != NULL && !box->IsDeleted()) {
			box->Delete();
		}
		vx = 0;
		vy = 0;
		ay = 0;
	}
}
void CKOOPA::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == LIFE) {
		l = x - KOOPA_BBOX_WIDTH / 2;
		t = y - KOOPA_BBOX_HEIGHT / 2;
		r = l + KOOPA_BBOX_WIDTH;
		b = t + KOOPA_BBOX_HEIGHT;
	}
	else {
		l = x - MAI_BBOX_WIDTH / 2;
		t = y - MAI_BBOX_HEIGHT / 2 ;
		r = l + MAI_BBOX_WIDTH;
		b = t + MAI_BBOX_HEIGHT;
	}
}