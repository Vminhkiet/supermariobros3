#include "TileMap.h"
#include "AssetIDs.h"
#include <fstream>
#include "Utils.h"


CTileSet::CTileSet()
{
}

CTileSet::~CTileSet()
{
	listTile.clear();
}

std::wstring s2ws2(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
void CTileSet::LoadFromFile(LPCWSTR imagePath) {
	

	// Add list tiles
	for (int i = 0; i < numOfRow; i++) {
		for (int j = 0; j < numOfColumn; j++) {
			RECT tmpRect = { j * tileWidth, i * tileHeight, (j + 1) * tileWidth, (i + 1) * tileHeight };
			int tmpID = i * numOfColumn + j + 1;
			listTile.insert(std::pair<int, RECT>(tmpID, tmpRect));
		}
	}
	
	// Add texture
	CTextures::GetInstance()->Add(ID_TEX_TILESET, imagePath);
	this->texture = CTextures::GetInstance()->Get(ID_TEX_TILESET);

}
void CTileSet::DrawTile(int id, D3DXVECTOR2 position, int alpha)
{
	RECT sourceRect = listTile[id];
	CGame::GetInstance()->Draw(position.x, position.y, texture, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom, alpha,22,20);
}

int CTileSet::GetTileWidth()
{
	return tileWidth;
}

int CTileSet::GetTileHeight()
{
	return tileHeight;
}

DWORD CTileMap::effectStart;

CTileMap::CTileMap()
{

	tileSet = new CTileSet();
	wStart = 0;
	wEnd = 100;

	effectStart = 0;
}

CTileMap::~CTileMap()
{
	for (int i = 0; i < tileRow; i++)
		delete[] mapData[i];
	delete mapData;
}

void CTileMap::LoadFromFile(LPCWSTR filePath)
{
	// Load info
	ifstream file(filePath);
	json j = json::parse(file);
	if (!file.is_open()) {
		DebugOut(L"Cannot open file: %s\n", filePath);
		return;
	}
	tileRow = j["/layers/0/height"_json_pointer].get<int>();
	tileColumn = j["/layers/0/width"_json_pointer].get<int>();
	height = j["/height"_json_pointer].get<int>();

	vector<int> data = j["/layers/0/data"_json_pointer].get<vector<int>>();

	// Map data from vector to matrix
	mapData = new int* [tileRow];
	for (int i = 0; i < tileRow; i++)
	{
		mapData[i] = new int[tileColumn];
		for (int j = 0; j < tileColumn; j++)
		{
			int tmp = i * tileColumn + j;
			mapData[i][j] = data[tmp];
		}
	}
	//string tilesetSource = j["tilesets"][0]["source"].get<std::string>();
	tileSet->tileWidth = j["tilesets"][0]["tilewidth"].get<int>();
	tileSet->tileHeight = j["tilesets"][0]["tileheight"].get<int>();
	tileSet->numOfColumn = j["tilesets"][0]["columns"].get<int>();
	int tileCount = j["tilesets"][0]["tilecount"].get<int>();
	std::string tmpPath = "textures\\" + j["tilesets"][0]["image"].get<std::string>();
	tileSet->numOfRow = (tileCount - 1) / tileSet->numOfColumn + 1;
	std::wstring sTmp = std::wstring(tmpPath.begin(), tmpPath.end());
	LPCWSTR imagePath = sTmp.c_str();
	file.close();
	// Load tileset
	tileSet->LoadFromFile(imagePath);
}

void CTileMap::Draw(D3DXVECTOR2 position, int alpha)
{
	float x, y;
	CGame::GetInstance()->GetCamPos(x, y);

	int wStart = x / tileSet->GetTileWidth();
	if (wStart < 0) wStart = 0;
	int hStart = y / tileSet->GetTileHeight();
	if (hStart < 0) hStart = 0;
	int wEnd = wStart + SCREEN_WIDTH / tileSet->GetTileWidth();
	if (wEnd > tileColumn) wEnd = tileColumn;
	int hEnd = hStart + SCREEN_HEIGHT / tileSet->GetTileHeight();
	if (hEnd > tileRow) hEnd = tileRow;

	if (effectStart > 0)
	{
		alpha = GetTickCount() % 100 > 50 ? 80 : 255;
		
		//if (alpha == 80)
			//CGame::GetInstance()->GetDirect3DDevice()->ColorFill(CGame::GetInstance()->GetBackBuffer(), NULL, D3DXCOLOR(0xBBBBBB));
	}
	for (int i = hStart; i < hEnd; i++)
	{
		for (int j = wStart; j < wEnd; j++)
		{
			if (mapData[i][j] == 0)
				continue;
			D3DXVECTOR2 pos;
			pos.x = position.x + j * tileSet->GetTileWidth() - x+10;
			pos.y = position.y + i * tileSet->GetTileHeight() - y-50;
			
			tileSet->DrawTile(mapData[i][j], pos, 255);
		}
	}
}

void CTileMap::Update(DWORD dt, vector<LPGAMEOBJECT>* object)
{
	if (effectStart > 0 && GetTickCount() - effectStart > TILEMAP_CROSS_EFFECT_TIME)
		effectStart = 0;
}

int CTileMap::GetWidth()
{
	return tileRow * tileSet->GetTileWidth();
}

int CTileMap::GetHeight()
{
	return tileColumn * tileSet->GetTileHeight();
}

