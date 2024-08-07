#include "Koopa.h"
#include "TopGround.h"
#include "Mario.h"
#include"ParaKoopa.h"
#include "PlayScene.h"
#include "QuestionBlock.h"
#include "Die.h"
#include "Brick.h"
#include "Koopa.h"
#include "Venus.h"
#include "Goomba.h"
#include "Para.h"
#include "Ground.h"
void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (res) {

		this->SetPosition(startx, starty);
		SetState(4);
		res = false;
		die = false;
		return;
	}
	if (die)
		return;
	if (roiy1 != -1 && roiy2 != -1) {
		if (x<roiy1 || x>roiy2) {
			
			roiy1 = -1;
			roiy2 = -1;
			isOnTop = 0;
		}
	}
	if (!die) {
		float cx, cy;
		float kx, ky;
		CGame::GetInstance()->GetCamPos(cx, cy);
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
		mario->GetSpeed(kx, ky);
		if ((cx - x > SCREEN_WIDTH / 2 - 200 && kx > 0) || (x - cx > SCREEN_WIDTH / 2 + 60) && kx < 0) {
			die = true;
			return;
		}
	}
	if (GetTickCount64() - dung > 3000 && state == MAI_MOVE) {
		SetState(3);
	}
	if (!(isOnPlatform || isOnTop==1)) {
		jump = false;
	}
	else if(GetTickCount64()-dibo>800) {
		jump = true;
	}
	if (!canh)
		jump = false;
	if (jump) {
		dibo = GetTickCount64();
		vy = -0.4f;
		isOnTop = 0;
	}
	if (GetTickCount64() - hoisinh > 200 && cho) {
		cho = false;
	}
	if (isOnTop) {
		isroi = 0;
	}
	if (!isOnTop)
		vy += ay * dt;

	vx += ax * dt;
	if (state == MAI2 && nhay) {
		if (vy > 0) {
			nhay = false;
		}
	}

	if (state == DIE2  && nhay) {
		if (vy > 0) {
			nhay = false;
		}
	}
	
	if ((state == DIE2) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	isOnPlatform = false;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CParaKoopa::Render() {
	if (res || die)
		return;
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
	else if (state == MAI2) {
		if (!lat) {
			if (!green)
				aniId = 13004;
			else
				aniId = 13012;
		}
		else {
			if (!green)
				aniId = 13019;
			else
				aniId = 13018;
		}
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
			if (mario->Getlevel() == 1) {
				mario->GetPosition(x, y);
				y -= 3;
			}
			else
			{
				mario->GetPosition(x, y);
			}

			if (draw > 0)
				x += 8;
			else
				x -= 8;
		}
		if (GetTickCount64() - hoisinh >= 5000 && !danghoisinh) {
			danghoisinh = true;
			stop = GetTickCount64();
		}
		if (danghoisinh && GetTickCount64() - stop < 500) {
			if (!lat) {
				if (!green)
					aniId = 13016;
				else
					aniId = 13017;
			}
			else {
				if (!green)
					aniId = 13022;
				else
					aniId = 13023;
			}
		}
		if (danghoisinh && GetTickCount64() - stop > 500) {
			SetState(0);

		}
	}
	else if (state == MAI_MOVE2) {
		if (!lat) {
			if (!green)
				aniId = 13005;
			else
				aniId = 13013;
		}
		else {
			if (!green)
				aniId = 13021;
			else
				aniId = 13020;
		}

	}
	int w = 16;
	int h = 16;
	if (state == LIFE2) {
		w = 16;
		h = 26;
	}
	if (canh) {
		if (vx < 0)
			aniId = 13014;
		else
			aniId = 13015;
	}
	if (state == DIE2) {
		if (!green)
			aniId = 13019;
		else
			aniId = 13018;
	}
	animations->Get(aniId)->Render(x, y, w, h);
	RenderBoundingBox();
}
void CParaKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
void CParaKoopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CVenus*>(e->obj)) {
		if (dynamic_cast<CVenus*>(e->obj)->getdie()) {
			return;
		}
		if (state == MAI_MOVE2)
		   dynamic_cast<CVenus*>(e->obj)->setdie(true);
		return;
	}
	if (!e->obj->IsBlocking() && e->obj->GetType() != 14 && e->obj->GetType() != 2 && (!dynamic_cast<CParaKoopa*>(e->obj)) && (!dynamic_cast<CKOOPA*>(e->obj)) || e->obj->GetType() == 16) return;
	if (dynamic_cast<Thebox*>(e->obj)) return;
	//if (dynamic_cast<CKOOPA*>(e->obj) &&( state == LIFE2 || canh ==true)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) {
		CGoomba* gooba = dynamic_cast<CGoomba*>(e->obj);
		if (state == LIFE2)
			return;
		if (state == MAI_MOVE2 && gooba->GetState() == 200) {
			return;
		}
	}
	if (dynamic_cast<CParaKoopa*>(e->obj) && state == MAI_MOVE2) {
		dynamic_cast<CParaKoopa*>(e->obj)->setcanh(false);
		dynamic_cast<CParaKoopa*>(e->obj)->setlat(true);
		dynamic_cast<CParaKoopa*>(e->obj)->SetState(3);
		return;
	}
	if (dynamic_cast<CPARA*>(e->obj)) {
		dynamic_cast<CPARA*>(e->obj)->Setrua(true);
		dynamic_cast<CPARA*>(e->obj)->SetState(200);
	}
	if (dynamic_cast<CKOOPA*>(e->obj)) {
		if(state == MAI_MOVE2)
		   dynamic_cast<CKOOPA*>(e->obj)->SetState(3);
		return;
	}
	if (dynamic_cast<CDie*>(e->obj))
	{
		die = true;
		return;
	}
	if (dynamic_cast<CGoomba*>(e->obj)) {
		if (state == MAI_MOVE2) {
			CGoomba* go = dynamic_cast<CGoomba*>(e->obj);
			go->Setrua(true);
			go->SetState(GOOMBA_STATE_DIE);
			return;
		}
	}
	if (dynamic_cast<CParaKoopa*>(e->obj)) return;

	if (e->obj->GetType() != 14) {

		if (e->ny != 0)
		{
			vy = 0;
			if (e->ny < 0) {
				isOnPlatform = true;
			}
			if (state == MAI) {
				vx = 0;
			}
		}
		else if (e->nx != 0 && state != MAI)
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
			if (lat) {
				vx = 0;
			}
			y = top->Gety() - KOOPA_BBOX_HEIGHT / 2;
			if (state != LIFE && !canh) {
				y += KOOPA_BBOX_HEIGHT/5;
			}
			//ay = 0;
			isOnTop = 1;
			return;
		}

	}
	else if (dynamic_cast<CQuestionblock*>(e->obj)) {
		CQuestionblock* qs = dynamic_cast<CQuestionblock*>(e->obj);
		if (e->nx != 0 && state == MAI_MOVE2) {
			qs->SetCham(true);
		}
	}
	else if (dynamic_cast<CBrick*>(e->obj))
	{
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		if (e->nx != 0 && state == MAI_MOVE) {
			brick->setdie(true);
		}
	}

}
void CParaKoopa::SetState(int state) {
	if (state == 0) {
		if (!die) {
			CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
			if (bicam) {
				float cx, cy;
				mario->Vacham();
				mario->GetSpeed(cx, cy);
				mario->SetSpeed(cx, cy - 0.1f);
				mario->Setcam(false);

			}
		}
		this->state = LIFE2;
		roiy1 = -1;
		roiy2 = -1;
		isOnTop = 0;
		canh = false;
		y -= 5;
		danghoisinh = false;
		bicam = false;
		lat = false;
		roiy1 = -1;
		roiy2 = -1;
		isOnTop = 0;
		this->ay = KOOPA_GRAVITY;
		if (!die)
			y -= 5;
		die_start = -1;
		danghoisinh = false;
		vx = -KOOPA_WALKING_SPEED;

	}
	else if (state == 1) {
		cho = true;
		this->state = MAI2;

		if (!lat)
			vx = 0;
		else {
			CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
			float cx, cy;
			mario->GetPosition(cx, cy);
			if (x < cx) {
				vx = -0.05;
			}
			else {
				vx = 0.05;
			}
		}
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

		this->state = MAI_MOVE2;
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
		float cx, cy;
		mario->GetPosition(cx, cy);
		if (cx > x)
			vx = -KOOPA_WALKING_SPEED * 6;
		else
			vx = KOOPA_WALKING_SPEED * 6;
	}
	else if (state == 3) {
		cho = true;
		hoisinh = GetTickCount64();
		this->state = DIE2;
		setlat(true);
		die_start = GetTickCount64();
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
		float cx, cy;
		mario->GetPosition(cx, cy);
		if (x < cx) {
			vx = -0.05;
		}
		else {
			vx = 0.05;
		}
	}
	else if (state == 4) {
		canh = true;
		this->SetPosition(startx, starty);
		state = LIFE2;
		danghoisinh = false;
		vx = -KOOPA_WALKING_SPEED;
	}
}
void CParaKoopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == LIFE2) {
		l = x - KOOPA_BBOX_WIDTH / 2;
		t = y - KOOPA_BBOX_HEIGHT / 2;
		r = l + KOOPA_BBOX_WIDTH;
		b = t + KOOPA_BBOX_HEIGHT;
	}
	else {
		l = x - MAI_BBOX_WIDTH / 2;
		t = y - MAI_BBOX_HEIGHT / 2;
		r = l + MAI_BBOX_WIDTH;
		b = t + MAI_BBOX_HEIGHT;
	}
}