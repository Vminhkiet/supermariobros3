#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

/*
	Initialize game object 
*/
CGameObject::CGameObject(float x, float y, LPTEXTURE tex)
{
	this->x = x;
	this->y = y;
	this->texture = tex;
}

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14
#define brick_VX 0.1f
#define BRICK_WIDTH 16
#define brick_VY 0.1f
#define BRICK_HEIGHT 16
void CMario::Update(DWORD dt)
{
	x += vx*dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {
		
		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}
void CBrick::Update(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
	int BackBufferWitdh = CGame::GetInstance()->GetBackBufferWidth();
	int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (x <= 0 || x >= BackBufferWitdh - BRICK_WIDTH) {
		vx = -vx;
		if (x <= 0) {
			x = 0;
		}
		else if (x >= BackBufferWitdh - BRICK_WIDTH) {
			x = (float)(BackBufferWitdh - BRICK_WIDTH);
		}
	}
	if (y <= 0 || y >= BackBufferHeight - BRICK_HEIGHT) {
		vy = -vy;
		if (y <= 0) {
			y = 0;
		}
		else if (y >= BackBufferHeight - BRICK_HEIGHT) {
			y = (float)(BackBufferHeight - BRICK_HEIGHT);
		}
	}
}
