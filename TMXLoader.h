#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <memory>
#include <iostream>

#include "rapidxml.hpp"

#include "TMXMap.h"
#include "TMXTileLayer.h"
#include "TMXTileSet.h"
#include "TMXTile.h"

class TMXLoader
{
    /* Class constructors & destructors */
public:
    TMXLoader();
    ~TMXLoader();

    /* Map methods */
public:
    void loadMap(std::string mapName, std::string filePath);
    TMXMap* getMap(std::string mapName);

    /* Debug methods */
public:
    void printMapData(std::string mapName);

    /* Map loading helper functions */
private:
    void loadMapSettings(std::unique_ptr<TMXMap> const& map, rapidxml::xml_node<>* parentNode);
    void loadTileSets(std::unique_ptr<TMXMap> const& map, rapidxml::xml_node<>* parentNode);
    void loadLayers(std::unique_ptr<TMXMap> const& map, rapidxml::xml_node<>* parentNode);
    void loadProperties(std::unordered_map<std::string, std::string>& propertiesMap, rapidxml::xml_node<>* parentNode);

    /* File loading helper functions */
private:
    bool loadFile(std::string filePath, std::string& fileContents);

    /* Unordered map container for loaded Maps */
private:
    std::unordered_map<std::string, std::unique_ptr<TMXMap>> m_mapContainer;
};