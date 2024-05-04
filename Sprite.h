#pragma once

#include "Texture.h"
#include "Game.h"

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);
	void DrawFlip(float x, float y, int spritewidth=0, int spriteheight=0);
	void Draw(float x, float y, int width=0, int height=0);
};

typedef CSprite* LPSPRITE;