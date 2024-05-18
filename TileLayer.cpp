#include "TileLayer.h"
#include "Textures.h"
#include "Utils.h"
#include "Sprites.h"
TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets) {
	this->m_Rowcount = rowcount;
	this->m_Colcount = colcount;
	this->m_Tilemap = tilemap;
	this->m_TileSize = tilesize;
	this->m_Tilesets = tilesets;

	for (unsigned int i = 0; i < m_Tilesets.size(); i++) {
		CTextures::GetInstance()->Add(m_Tilesets[i].name, ToLPCWSTR("map/" + m_Tilesets[i].source));
	}
}
void TileLayer::Render() {
	for (unsigned int i = 0; i < m_Rowcount; i++) {
		for (unsigned int j = 0; j < m_Colcount; j++) {
			int tileID = m_Tilemap[i][j];
			if (tileID == 0)
				continue;
			else {
				int index;
				if (m_Tilesets.size() > 1) {
					for (unsigned int k = 1; k < m_Tilesets.size(); k++) {
						if (tileID > m_Tilesets[k].Firstid && tileID < m_Tilesets[k].Lastid) {
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].Lastid;
							index = k;
							break;
						}
					}
				}
				Tileset ts = m_Tilesets[index];
				int tileRow = tileID / ts.columnscount;
				int tileCol = tileID - tileRow * ts.columnscount - 1;

				if (tileID % ts.columnscount == 0) {
					tileRow--;
					tileCol = ts.columnscount - 1;
				}
				CSprites::GetInstance()->DrawTextureRegion(ts.name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileCol);
			}
		}
	}
}