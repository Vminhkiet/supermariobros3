#include <Windows.h>

#include "debug.h"
#include "Game.h"
#include "textures.h"

CTextures* CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath)
{
	textures[id] = CGame::GetInstance()->LoadTexture(filePath);
}
void CTextures::Add(string name, LPCWSTR filePath)
{
	textures1[name] = CGame::GetInstance()->LoadTexture(filePath);
}

LPTEXTURE CTextures::Get(int i)
{
	LPTEXTURE t = textures[i];
	if (t == NULL)
		DebugOut(L"[ERROR] Texture Id %d not found !\n", i);
	
	return t;
}
LPTEXTURE CTextures::Get(string i)
{
	LPTEXTURE t = textures1[i];
	if (t == NULL)
		DebugOut(L"[ERROR] Texture Id %d not found !\n", i);

	return t;
}

/*
	Clear all loaded textures
*/
void CTextures::Clear()
{
	for (auto x : textures)
	{
		LPTEXTURE tex = x.second;
		if (tex != NULL) delete tex;
	}

	textures.clear();
}



