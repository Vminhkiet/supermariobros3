#include "MapParser.h"
bool MapParser::Load() {
	return Parse("level1", "map.tmx");
}
Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid",&tileset.Firstid);
	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.Lastid = (tileset.Firstid + tileset.TileCount) - 1;

	xmlTileset->Attribute("columns", &tileset.columnscount);
	tileset.columnscount = tileset.TileCount / tileset.columnscount;
	xmlTileset->Attribute("tilewidth", &tileset.TileSize);
	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.source = image->Attribute("source");
	return tileset;
}
TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount) {
	TiXmlElement* data;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("data")) {
			data = 0;
			break;
		}
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
	for (int row = 0; row = rowcount; row++) {
		for (int col = 0; col = colcount; col++) {
			getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good())
				break;
		}
	}
	return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}

bool MapParser::Parse(std::string id, std::string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cerr << "Failed to load: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowcount, colcount, tilesize = 0;
	root->Attribute("width", &colcount);
	root->Attribute("height", &rowcount);
	root->Attribute("tilewidth", &tilesize);

	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	GameMap* gamemap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("layer")) {
			TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayer.push_back(tilelayer);
		}
	}

	m_MapDict[id] = gamemap;
	return true;
}