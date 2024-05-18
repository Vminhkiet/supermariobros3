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
	unordered_map<string,LPTEXTURE> textures1;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath);
	void Add(string name, LPCWSTR filePath);
	LPTEXTURE Get(int i);
	LPTEXTURE Get(string i);
	void Clear();

	static CTextures* GetInstance();
};