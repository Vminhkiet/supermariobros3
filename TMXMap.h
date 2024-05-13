#pragma once
#include "TMXTileSet.h"
#include "TMXTileLayer.h"

class TMXMap final
{
public:
    /* Class constructors & destructors */
    TMXMap();
    ~TMXMap() noexcept;

    /* Setter functions for map settings */
    void setMapSettings(
        std::vector<std::string> const& mapData,
        std::unordered_map<std::string, std::string> const& mapProps) noexcept;

    /* Getter functions for map settings */
    float getVersion() const noexcept;
    unsigned getWidth() const noexcept;
    unsigned getHeight() const noexcept;
    unsigned getTileWidth() const noexcept;
    unsigned getTileHeight() const noexcept;
    std::array<unsigned, 3> getBackgroundColor() const noexcept;
    std::string getOrientation() const noexcept;
    std::string getRenderOrder() const noexcept;

    /* TileSets */
    void addTileSet(TMXTileSet const& newTileSet) noexcept;
    TMXTileSet* getTileset(std::string const& tileSetName) noexcept;

    /* Layers */
    void addLayer(TMXTileLayer const& newLayer) noexcept;
    TMXTileLayer* getLayer(std::string const& layerName) noexcept;

    /* Debug functions */
    void printData();

private:
    /* Map variables */
    float m_version;
    unsigned m_width, m_height;
    unsigned m_tileWidth, m_tileHeight;
    std::array<unsigned, 3> m_backgroundColour;
    std::string m_orientation;
    std::string m_renderOrder;

    /* User-defined properties */
    std::unordered_map<std::string, std::string> m_propertiesMap;

    std::vector<TMXTileLayer> m_layerVector;
    std::vector<TMXTileSet> m_tileVector;
};