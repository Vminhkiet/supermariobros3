#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "Textures.h"

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

/*
	Clear all loaded sprites
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}
void CSprites::DrawTextureRegion(string name, int tileSize, int x, int y, int row, int frame) {
    int top = tileSize * frame;
    int left = tileSize * (row - 1);


    CSprite sprite(left,top,left+tileSize,top+tileSize,CTextures::GetInstance()->Get(name));

    sprite.Draw(x,y);
}
