#pragma once
#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"
class MapParser
{
private:
	static MapParser* m_Instance;
	std::map<std::string, GameMap*> m_MapDict;
	

	bool Parse(std::string id, std::string source);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer,TilesetList tilesets,int tilesize,int rowcount,int colcount);
public:
	MapParser() {}
	inline static MapParser* GetInstance() {
		return m_Instance = (m_Instance != nullptr) ? m_Instance : new MapParser();
	}
	bool Load();
	void Clean();
	inline GameMap* GetMaps(std::string id) { return m_MapDict[id]; }
};

