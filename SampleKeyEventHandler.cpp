#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	if (mario->getintro() == 0)
		return;
	if (game->GetCurrentScene()->getid() == 3) {
		switch (KeyCode)
		{
		case DIK_S:

			break;
		}
		return;
	}
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		if (!fly) {
			fly = true;
			if (mario->checkfly()) {
				mario->SetState(MARIO_STATE_FLY);
			}
			else {
				mario->SetState(MARIO_STATE_JUMP);
			}
		}
			
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_4:
		mario->SetPosition(2250, -300);
		break;
	case DIK_5:
		mario->SetPosition(1200, 0);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_A:
		if (!a) {
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			a = true;
			float vx, vy;
			mario->GetSpeed(vx, vy);
			if (vy <= 0)
				mario->SetDanh(true);
			else
				mario->SetSpeed(vx, 0);
		}
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->getintro() == 0)
		return;
	if (game->GetCurrentScene()->getid() == 3) {
		switch (KeyCode)
		{
		case DIK_S:

			break;
		}
		return;
	}
	switch (KeyCode)
	{
	case DIK_S:
		fly = false;
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->SetDanh(false);
		a = false;
		fly = false;
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (CGame::GetInstance()->GetCurrentScene()->getpause())
		return;
	if (mario->getintro() == 0)
		return;
	if (game->GetCurrentScene()->getid() == 3) {
		bool l, r, t, b;
		mario->gethuongdi(l, r, t, b);
		if (!mario->getduocphep())
			return;
		if (game->IsKeyDown(DIK_RIGHT) && r) {
			mario->SetState(100);
			mario->setduocphep(false);
		}
		else if (game->IsKeyDown(DIK_LEFT) && l) {
			mario->SetState(200);
			mario->setduocphep(false);
		}
		else if (game->IsKeyDown(DIK_DOWN) && b) {
			mario->SetState(199);
			mario->setduocphep(false);
		}
		else if (game->IsKeyDown(DIK_UP) && t) {
			mario->SetState(198);
			mario->setduocphep(false);
		}
		return;
	}
	
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A)) {
			mario->Setcam(true);
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else {
			mario->Setcam(false);
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A)) {
			mario->Setcam(true);
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		}
		else {
			mario->Setcam(false);
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	}
	else {
		if (game->IsKeyDown(DIK_A))
			mario->Setcam(true);
		else
			mario->Setcam(false);
		mario->SetState(MARIO_STATE_IDLE);
	}
}