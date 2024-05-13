
#include <iostream>
#include "TMXTile.h"

TMXTile::TMXTile(unsigned TileID, std::unordered_map<std::string, std::string> const& propertiesMap)
    : m_TileID{ TileID }, m_propertiesMap{ propertiesMap } {}

TMXTile::~TMXTile() noexcept
{
    m_propertiesMap.clear();
    std::unordered_map<std::string, std::string>{}.swap(m_propertiesMap);
}

unsigned TMXTile::getTileID() const noexcept { return m_TileID; }
std::string TMXTile::getProperty(std::string const& propertyName) noexcept
{
    auto it = m_propertiesMap.find(propertyName); 
    if (it != m_propertiesMap.end()) {
        return it->second;
    }
    return {};
}


void TMXTile::printData()
{
    std::cout << "Tile ID: " << m_TileID << "\n Tile Properties: " << std::endl;
    for (auto index = m_propertiesMap.begin(); index != m_propertiesMap.end(); ++index)
    {
        std::cout << "\n" << index->first << " - " << index->second << std::endl;
    }
}