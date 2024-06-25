#pragma once
#include <d3d.h>
#include <d3d10.h>
#include "json.hpp"
#include "debug.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <d3d10.h>
#include <d3dx10.h>
#define TILEMAP_CROSS_EFFECT_TIME		1000


using json = nlohmann::json;

class CLayer {
private:
	string name;
	int tileRow;
	int tileColumn;
	bool visible = true;
	int count = 0;
	int** data;
	vector<pair<int, int>> toadocell;

public:
	CLayer() : tileRow(0), tileColumn(0), data(nullptr),name("") {}
	~CLayer() {
		if (data) {
			for (int i = 0; i < tileRow; i++) {
				delete[] data[i];
			}
			delete[] data;
		}
	}

	friend class CTileMap;
};

typedef CLayer* LPLAYER;

class CTileSet
{
private:
	int tileWidth;
	int tileHeight;
	int numOfColumn;
	int numOfRow;

	map<int, RECT> listTile;
	LPTEXTURE texture;
public:
	CTileSet();
	~CTileSet();

	void LoadFromFile(LPCWSTR imagePath);
	void DrawTile(int id, D3DXVECTOR2 position, int alpha = 255);
	int GetTileWidth();
	int GetTileHeight();
	friend class CTileMap;
};

typedef CTileSet* LPTILESET;

class CTileMap
{
private:
	int tileRow;
	int tileColumn;
	int height;
	LPTILESET tileSet;
	vector<LPLAYER> layers;

	int wStart;
	int wEnd;
	bool load=false;

	static DWORD effectStart;
public:
	CTileMap();


	void LoadFromFile(LPCWSTR filePath);
	void Draw(D3DXVECTOR2 position, int alpha = 255,bool background=false);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* object = NULL);

	int GetWidth();
	int GetHeight();
	bool getload() {
		return load;
	}
	static void StartEffect() { effectStart = GetTickCount(); }
	
};

typedef CTileMap* LPTILEMAP;