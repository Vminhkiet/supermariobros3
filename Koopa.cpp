#include "Koopa.h"
#include "TopGround.h"
#include "Mario.h"
#include "PlayScene.h"
#include "QuestionBlock.h"
#include "Goomba.h"
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
	if ((state == DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
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
			if (nx > 0) aniId = 13007;
			else aniId = 13006;
		}
		else if (vx > 0)
		{
			aniId = 13003;
		}
		else // vx < 0
		{
			aniId = 13002;
		}
	}
	else if (state == MAI) {
		aniId = 13004;
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
		if (!mario->getcam() && bicam) {
			bicam = false;
			state = MAI_MOVE;
			float mx, my;
			mario->GetPosition(mx, my);
			if (mx > x) {
				huongdichuyen = false;
			}
			else
				huongdichuyen = true;
			
		}
		if (bicam) {
			int nxmario = currentScene->GetPlayer()->getnx();
			currentScene->GetPlayer()->GetPosition(x, y);
			if (nxmario > 0)
				x += 8;
			else if (nxmario < 0)
				x -= 8;
		}
	}
	else if (state == MAI_MOVE) {
		aniId = 13005;
		
	}
	int w = 16;
	int h = 16;
	if (state == LIFE) {
		w = 16;
		h = 26;
	}
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
	if (e->obj->GetType() != 14) {
		if (e->ny != 0)
		{
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
		if (e->obj->GetType() != 14) {
			if (e->ny != 0)
			{
				vy = 0;
			}
			else if (e->nx != 0)
			{
				vx = -vx;
			}
		}
		if (isroi) {
			roiy1 = top->getx();
			roiy2 = roiy1 + top->getwidth();
			vy = 0;
			y = top->Gety() - KOOPA_BBOX_HEIGHT / 2;
			//ay = 0;
			isOnTop = 1;
			return;
		}

	}
	else if (dynamic_cast<CQuestionblock*>(e->obj)) {
		CQuestionblock* qs = dynamic_cast<CQuestionblock*>(e->obj);
		if (e->nx != 0) {
			qs->SetCham(true);
			vx *= -1;
		}
	}
	else if (dynamic_cast<CGoomba*>(e->obj)) {
		if (state == MAI_MOVE) {
			CGoomba* go = dynamic_cast<CGoomba*>(e->obj);
			go->Setrua(true);
			go->SetState(GOOMBA_STATE_DIE);
			vx *= -1;
		}
	}
}
void CKOOPA::SetState(int state){
	if (state == 0) {
		this->state = LIFE;
	}
	else if (state == 1) {
		this->state = MAI;
		y += 5;
	}
	else if (state == 2) {
		this->state = MAI_MOVE;
	}
	else if (state == 3) {
		this->state = DIE;
		die_start = GetTickCount64();
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