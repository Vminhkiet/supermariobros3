

#include <iostream>
#include "TMXTileLayer.h"

TMXTileLayer::TMXTileLayer(
    std::string const& name,
    unsigned width, unsigned height,
    std::unordered_map<std::string, std::string> const& layerProperties,
    std::vector<std::vector<unsigned>> const& tileVector)
    : m_name{ name }, m_width{ width }, m_height{ height },
    m_layerProperties{ layerProperties }, m_tileVector{ tileVector } {}

TMXTileLayer::~TMXTileLayer() noexcept
{
    m_tileVector.clear();
    std::vector<std::vector<unsigned>>{}.swap(m_tileVector);

    m_layerProperties.clear();
    std::unordered_map<std::string, std::string>{}.swap(m_layerProperties);
}

unsigned TMXTileLayer::getWidth() const noexcept { return m_width; }
unsigned TMXTileLayer::getHeight() const noexcept { return m_height; }

std::string TMXTileLayer::getName() const noexcept { return m_name; }
std::vector<std::vector<unsigned>> TMXTileLayer::getTiles() const noexcept { return m_tileVector; }
std::string TMXTileLayer::getProperty(std::string const& propertyName) noexcept
{
    auto it = m_layerProperties.find(propertyName); 
    if (it != m_layerProperties.end()) {
        return it->second;
    }
    std::cout << "TMXLoader: property '" << propertyName << "' not found." << std::endl;
    return "";
}

void TMXTileLayer::printData()
{
    std::cout << "\nName: " << m_name
        << "\nWidth: " << m_width
        << "\nHeight: " << m_height
        << "\nLayer Properties:";

    for (auto index = m_layerProperties.begin(); index != m_layerProperties.end(); ++index)
        std::cout << "\n"
        << index->first << " - " << index->second << std::endl;

    std::cout << "\nTiles: ";
    for (unsigned int row = 0; row < m_width; ++row)
        for (unsigned int column = 0; column < m_height; ++column)
            std::cout << m_tileVector[row][column] << " ";
    std::cout << std::endl;
}