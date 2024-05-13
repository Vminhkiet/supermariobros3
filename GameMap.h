#pragma once
#include "Layer.h"
#include <vector>

class GameMap
{
private:
	std::vector<Layer*> m_MapLayer;
	friend class MapParser;
public:
	
	GameMap() {}
	void Render();
	void Update();
	std::vector<Layer*> GetMapLayer() { return m_MapLayer; }
};

