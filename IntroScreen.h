#pragma once
#include "Mario.h"
#include "TileMap.h"

class CScene1
{
	static CScene1* __instance;
	CMario* mariored;
	LPTILEMAP tileMap;
	vector<CGameObject*> objects;
public:

	static CScene1* GetInstance();
	void Loadfile();
	void LoadResource(string s);
	void Setitem(vector<LPGAMEOBJECT>& obj, LPGAMEOBJECT& player);
	void Update(DWORD dt);
	void Render();
};
