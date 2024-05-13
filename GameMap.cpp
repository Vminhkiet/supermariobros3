#include "GameMap.h"
void GameMap::Render() {
	for (unsigned int i = 0; i < m_MapLayer.size(); i++)
		m_MapLayer[i]->Render();
}
void GameMap::Update() {
	for (unsigned int i = 0; i < m_MapLayer.size(); i++)
		m_MapLayer[i]->Update();
}