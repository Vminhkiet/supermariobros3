#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

	float texWidth = (float)tex->getWidth();
	float texHeight = (float)tex->getHeight();

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = this->left / texWidth;
	sprite.TexCoord.y = this->top / texHeight;

	int spriteWidth = (this->right - this->left + 1);
	int spriteHeight = (this->bottom - this->top + 1);
	sprite.TexSize.x = spriteWidth / texWidth;
	sprite.TexSize.y = spriteHeight / texHeight;

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	
}

void CSprite::Draw(float x, float y, int spritewidth, int spriteheight)
{
	CGame* g = CGame::GetInstance();
	float cx, cy;
	g->GetCamPos(cx, cy);

	cx = (FLOAT)floor(cx);
	cy = (FLOAT)floor(cy);

	D3DXMATRIX matTranslation;
	
	x = (FLOAT)floor(x);
	y = (FLOAT)floor(y);
	if (spritewidth == 0 && spriteheight == 0) {
		spritewidth = (this->right - this->left + 1);
		spriteheight = (this->bottom - this->top + 1);
	}
	D3DXMatrixScaling(&this->matScaling, (FLOAT)spritewidth, (FLOAT)spriteheight, 1.0f);
	D3DXMatrixTranslation(&matTranslation, x - cx, g->GetBackBufferHeight() - y + cy, 0.1f);

	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

