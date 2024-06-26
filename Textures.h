#pragma once
#include <unordered_map>
#include <d3dx10.h>
#include <string>
#include "Texture.h"

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures* __instance;

	unordered_map<int, LPTEXTURE> textures;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath);

	LPTEXTURE Get(int i);
	void Clear();

	static CTextures* GetInstance();
};