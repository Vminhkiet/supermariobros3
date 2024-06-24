#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include"Thebox.h"
#include "Game.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Coin.h"
#include "Swap.h"
#include "Bullet.h"
#include "Portal.h"
#include "Koopa.h"
#include "Venus.h"
#include "Leaf.h"
#include "Para.h"
#include "QuestionBlock.h"
#include "TopGround.h"
#include "Collision.h"
#include "PlayScene.h"
#include "Brick.h"

int CMario::getintro() {
	return intro;
}
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	if (CGame::GetInstance()->GetCurrentScene()->getpause()) {
		if (GetTickCount64() - st > 1500) {
			hoalon = false;
			CGame::GetInstance()->GetCurrentScene()->setpause(false);
			st = GetTickCount64();
		}
		return;
	}

	if (dichchuyen && down && cground) {
		dangdichuyen = true;
		float cx, cy;
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		currentScene->findgetposition(cx, cy, name);
		x = cx;
		y = cy;
		len = 2;
		vitri = cy;
	}
	if (dichchuyen && up && !cground) {
		dangdichuyen = true;
		float cx, cy;
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		currentScene->findgetposition(cx, cy, name);
		x = cx;
		y = cy;
		len = 1;
		vitri = cy;
	}
	if (dangdichuyen) {
		
		if (len == 1) {
			if (vitri - 50 > y) {
				dangdichuyen = false;
				dichchuyen = false;
			}
			else y--;
		}
		else if (len == 2) {
			if (vitri + 50 < y) {
				dangdichuyen = false;
				dichchuyen = false;
			}
			else y++;
		}
		return;
	}
	else {

		len = 0;
	}
	if (isOnPlatform) {
		fly = false;
	}
	if (untouchable != 0) {
		if (GetTickCount64() - st > 50) {
			st = GetTickCount64();
			nhapnhay = !nhapnhay;
		}
	}
	draw = false;
	if (!cammai) {
		dacam = false;
	}
	if (GetState()==MARIO_STATE_JUMP ) {
		ay = MARIO_GRAVITY;
	}
	else if (roiy1 != -1 && roiy2 != -1) {
		if (x<roiy1 || x>roiy2) {
			roiy1 = -1;
			roiy2 = -1;
			isOnTop = 0;
		}
	}
	if (isOnTop) {
		isroi = 0;
	}
	if(!isOnTop)
	  vy += ay * dt;

	vx += ax * dt;
	
	if (abs(vx) > abs(maxVx)) { vx = maxVx;  }
	
	
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME + 1500) 
	{
		nhapnhay = false;
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount64() - isfly > 300 && fly)
	{
		isfly = GetTickCount64();
		//fly = false;
	}

	if (intro == 0 && !mariogreen) {
		isOnPlatform = true;
	}
	else {
		isOnPlatform = false;
		//isOnTop = 0;
	}
	
	CCollision::GetInstance()->Process(this, dt, coObjects);
	
}

void CMario::OnNoCollision(DWORD dt)
{
	if (!dangdichuyen) {
		x += vx * dt;
		y += vy * dt;
	}
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dangdichuyen) return;
	if (dynamic_cast<Thebox*>(e->obj))
		return;
	if (e->obj->IsBlocking())
	{
		if (e->ny != 0)
		{
			vy = 0; // Đặt tốc độ rơi bằng 0 khi va chạm theo trục y
			if (e->ny < 0)
			{
				isOnPlatform = true; // Điều chỉnh vị trí để đứng trên nền
			}
		}
		else if (e->nx != 0)
		{
			vx = 0; // Đặt tốc độ ngang bằng 0 khi va chạm theo trục x
		}
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if(dynamic_cast<Swap*>(e->obj))
		OnCollisionWithSwap(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMario*>(e->obj))
		OnCollisionWithMario(e);
	else if (dynamic_cast<CMUSHROOM*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLEAF*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CQuestionblock*>(e->obj))
		OnCollisionWithQuestionblock(e);
	else if (dynamic_cast<CBullet*>(e->obj))
		OnCollisionWithBullet(e);
	else if (dynamic_cast<CKOOPA*>(e->obj))
		OnCollisionWithTroopa(e);
	else if (dynamic_cast<CVenus*>(e->obj))
		OnCollisionWithBullet(e);
	else if (dynamic_cast<CPARA*>(e->obj))
		OnCollisionWithPara(e);
	else if (dynamic_cast<CTop*>(e->obj)) {
		CTop* top = dynamic_cast<CTop*>(e->obj);
		if (e->ny < 0) {
			isroi = 1;
		}

		if (isroi) {
			roiy1 = top->getx();
			roiy2 = roiy1 + top->getwidth();
			vy = 0;
			if (level == MARIO_LEVEL_SMALL) {
				y = top->Gety() - MARIO_SMALL_BBOX_HEIGHT / 2;
			}
			else {
				y = top->Gety() - MARIO_BIG_BBOX_HEIGHT/2;
			}
			//ay = 0;
			isOnTop = 1;
			isOnPlatform = true;
			return;
		}
		
	}
	
	
}
void CMario::OnCollisionWithSwap(LPCOLLISIONEVENT e) {
	dichchuyen = true;
	name = dynamic_cast<Swap*>(e->obj)->getname();
	cground = dynamic_cast<Swap*>(e->obj)->getdown();
}
void CMario::OnCollisionWithKick(LPCOLLISIONEVENT e) {
	if (level == 3 && danh ) {
		if ((this->nx < 0 && e->obj->getnx() > 0) || (this->nx > 0 && e->obj->getnx() < 0)) {
			if (dynamic_cast<CVenus*>(e->obj)) {
				e->obj->Delete();
			}
			else if (dynamic_cast<CGoomba*>(e->obj)) {

			}
			else if (dynamic_cast<CBrick*>(e->obj)) {

			}
			
		}
	}
}
void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e) {
	if (untouchable == 0) {
		if (level > MARIO_LEVEL_SMALL) {

			st = GetTickCount64();
			CGame::GetInstance()->GetCurrentScene()->setpause(true);
			hoalon = true;
			isOnTop = false;
			level = MARIO_LEVEL_SMALL;
			if (e->obj->GetType() == 16)
				e->obj->Delete();
			StartUntouchable();
		}
		else {
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e) {
	if (level == MARIO_LEVEL_SMALL) {
		
		e->obj->Delete();
		st = GetTickCount64();
		CGame::GetInstance()->GetCurrentScene()->setpause(true);
		hoalon = true;

		level = MARIO_LEVEL_BIG;
		y -= MARIO_BIG_BBOX_HEIGHT / 4;
		
		SetLevel(level);
	}
}
void CMario::OnCollisionWithMario(LPCOLLISIONEVENT e) {
	CMario* mario = dynamic_cast<CMario*>(e->obj);

	if (mario->GetState() == MARIO_STATE_JUMP)
	{
		ay = 0;
		y -= 10;
		SetState(MARIO_STATE_SIT);
		mario->vy = -MARIO_JUMP_RUN_SPEED_Y;
	}


}

void CMario::OnCollisionWithQuestionblock(LPCOLLISIONEVENT e){
	if (e->ny > 0 ) {
		CQuestionblock* ques= dynamic_cast<CQuestionblock*>(e->obj);
		ques->SetCham(true);
	}
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e) {
	if (level == MARIO_LEVEL_BIG) {
		CLEAF* leaf = dynamic_cast<CLEAF*>(e->obj);

		SetLevel(MARIO_LEVEL_RACOON);

		e->obj->Delete();
	}

}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					st = GetTickCount64();
					CGame::GetInstance()->GetCurrentScene()->setpause(true);
					hoalon = true;

					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}
void CMario::OnCollisionWithTroopa(LPCOLLISIONEVENT e) {
	CKOOPA* p = (CKOOPA*)e->obj;
	int pstate = p->Getstate();
	
	if (pstate == 0) {
		if (e->ny < 0)
		{
			if (pstate == 0)
			{
				p->SetState(1);
				vy = -MARIO_JUMP_DEFLECT_SPEED +0.2f;
			}
		}
		else // hit by Troopa
		{
			if (untouchable == 0)
			{
				if (pstate == 0 || pstate == 2)
				{
					if (untouchable == 0) {
						if (level > MARIO_LEVEL_SMALL)
						{
							st = GetTickCount64();
							CGame::GetInstance()->GetCurrentScene()->setpause(true);
							hoalon = true;
							isOnTop = false;
							level = MARIO_LEVEL_SMALL;
							StartUntouchable();
						}
						else
						{
							DebugOut(L">>> Mario DIE >>> \n");
							SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
		}
	}
	if (pstate == 1) {
		if (!cammai) {
			dacam = false;
			p->SetState(2);
			p->setcam(false);
			if (nx > 0) {
				p->sethuong(true);
			}
			else if (nx < 0) {
				p->sethuong(false);
			}
		}
		else {
			dacam = true;
			p->setcam(true);
		}
	}
	if (pstate == 2) {
		if (untouchable == 0) {
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}

}
void CMario::OnCollisionWithPara(LPCOLLISIONEVENT e) {
	CPARA* goomba = dynamic_cast<CPARA*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->getcanh()) {
			goomba->setcanh(false);
			goomba->Setvy(0);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					st = GetTickCount64();
					CGame::GetInstance()->GetCurrentScene()->setpause(true);
					hoalon = true;

					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;

	if (!(isOnPlatform || isOnTop))
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (!dacam) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = 1005;
				else
					aniId = 1006;
			}
		}
		else
		{
			if (!dacam) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
			else {
				draw = false;
				if (nx >= 0) {
					aniId = 1005;
					draw = true;
				}
				else
					aniId = 1006;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (!dacam) {
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else {
					draw = false;
					if (nx > 0) {
						aniId = 1003;
						draw = true;
					}
					else aniId = 1004;
				}
			}
			else if (vx > 0)
			{
				if (!dacam) {
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
				else {
					draw = true;
					aniId = 1015;
				}
			}
			else // vx < 0
			{
				if (!dacam) {
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
				else {
					aniId = 1002;
					draw = false;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	
	if (!(isOnPlatform||isOnTop))
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
		if (dacam) {
			draw = false;
			if (nx >= 0) {
				draw = true;
				aniId = 1010;
			}
			else
				aniId = 1009;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
				if (dacam) {
					draw = false;
					if (nx > 0) {
						aniId = 1012;
						draw = true;
					}
					else
						aniId = 1011;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
				if (dacam) {
					aniId = 1008;
					draw = true;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
				if (dacam) {
					aniId = 1007;
					draw = false;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
int CMario::GetAniIdRacoon()
{
	int aniId = -1;

	if (!(isOnPlatform || isOnTop))
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT+30;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT+30;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT+30;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT+30;
		}
		if (dacam) {
			draw = false;
			if (nx >= 0) {
				draw = true;
				aniId = 1010;
			}
			else
				aniId = 1009;
		}
		if (fly) {

		}
		else {
			if (nx >= 0) {
				aniId = 1041;
			}
			else {
				aniId = 1051;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT+30;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT+30;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT+30;
				else aniId = ID_ANI_MARIO_IDLE_LEFT+30;
				if (dacam) {
					draw = false;
					if (nx > 0) {
						aniId = 1012;
						draw = true;
					}
					else
						aniId = 1011;
				}
				if (danh && !dacam) {
					if (nx > 0) {
						aniId = 1061;
					}
					else aniId = 1060;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT+30;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT+30;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT+30;
				if (dacam) {
					aniId = 1008;
					draw = true;
				}
				if (danh && !dacam) {
					aniId = 1061;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT + 30;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT + 30;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT + 30;
				if (dacam) {
					aniId = 1007;
					draw = false;
				}
				if (danh && !dacam) {
					aniId = 1060;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT+30;
	
	return aniId;
}

void CMario::Render()
{
	if (!nhapnhay) {
		CAnimations* animations = CAnimations::GetInstance();
		int aniId = -1;
		if (GetTickCount64() - sdanh > 200 && danh) {
			danh = false;
		}
		if (state == MARIO_STATE_DIE)
			aniId = ID_ANI_MARIO_DIE;
		else if (level == MARIO_LEVEL_BIG)
			aniId = GetAniIdBig();
		else if (level == MARIO_LEVEL_SMALL)
			aniId = GetAniIdSmall();
		else if (level == MARIO_LEVEL_RACOON)
			aniId = GetAniIdRacoon();
		if (change) {
			if (nx > 0) {
				aniId = 803;
			}
			else {
				aniId = 802;
			}
		}
		if (hoalon) {
			if (nx > 0) {
				aniId = 803;
			}
			else {
				aniId = 802;
			}
		}
		
		animations->Get(aniId)->Render(x, y);
	}

	if(mariogreen) RenderBoundingBox();
	RenderBoundingBox();
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 
	if (dacam) {
		if (state == MARIO_STATE_RUNNING_RIGHT)
			state = MARIO_STATE_WALKING_RIGHT;
		else if (state == MARIO_STATE_RUNNING_LEFT) {
			state = MARIO_STATE_WALKING_LEFT;
		}
	}
	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		up = true;
		if (isSitting) break;
		
		if (abs(vx) >= MARIO_RUNNING_SPEED && !(isOnTop == 1 || isOnPlatform)) {
			fly = true;
			isfly = GetTickCount64();
			break;
		}
		
		if (isOnPlatform || isOnTop==1)
		{
			isroi = 0;
			isfly = GetTickCount64();
			isOnTop = 0;
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_FLY:
		up = true;
		if (vy > 0.5f || abs(ax) < MARIO_ACCEL_RUN_X) {
			fly = false;
			vy = 0.0f;
		}
		else if (fly) {
			vy = -0.3f;
			isfly = GetTickCount64();
		}
		break;
	case MARIO_STATE_RELEASE_JUMP:
		up = false;
		isroi = 1;
		if (!(isOnPlatform || isOnTop == 1) && level == 3 && !fly) {
			if(vy>0.0f)
			   vy = 0.0f;
			break;
		}
		if (vy < 0 && !fly) vy += MARIO_JUMP_SPEED_Y / 2;

		break;
	case MARIO_STATE_ROICHAM:
		if (!(isOnPlatform || isOnTop == 1) && level == 3) {
			if(vy > 0.1f)
			   vy = 0.1f;
			
		}
		break;
	case MARIO_STATE_SIT:
		if ((isOnTop == 1 || isOnPlatform))
		    down = true;
		if(!dacam)
		if ((isOnTop == 1 ||isOnPlatform) && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			ax = 0;
			
			if(isOnTop == 0)
			  y -=MARIO_SIT_HEIGHT_ADJUST;
			else {
				y += MARIO_SIT_HEIGHT_ADJUST;
			}
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		down = false;
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			if (level == 3) {
				y -= 10;
				vy = 0.1f;
			}
			if(isOnTop == 0)
			    y -= MARIO_SIT_HEIGHT_ADJUST;

		}
		break;
	case MARIO_STATE_IDLE:
		isroi = 0;
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2 ;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2 ;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACOON) {
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACOON_BBOX_WIDTH / 2 ;
			top = y - MARIO_RACOON_BBOX_HEIGHT / 2 ;
			right = left + MARIO_RACOON_BBOX_WIDTH ;
			bottom = top + MARIO_RACOON_BBOX_HEIGHT;
				if (nx < 0) {
					left -= 3;
				}
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2 ;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	
	level = l;
}

