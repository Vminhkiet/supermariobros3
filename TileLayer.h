#pragma once
#include "Layer.h"
#include <string>
#include <vector>
struct Tileset {
	int Firstid, Lastid;
	int rowscount, columnscount;
	int TileCount, TileSize;
	std::string name, source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;
class TileLayer : public Layer
{
private:
	int m_TileSize;
	int m_Rowcount,m_Colcount;
	TileMap m_Tilemap;
	TilesetList m_Tilesets;
public:
	TileLayer(int tilesize,int rowcount,int colcount,TileMap tilemap,TilesetList tilesets);
	virtual void Render();
	void Update(){ }
	inline TileMap GetTileMap() { return m_Tilemap; }

};

