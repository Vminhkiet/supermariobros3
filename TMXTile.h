#pragma once
#include <string>
#include <unordered_map>

class TMXTile final
{
public:
    /* Class constructors & destructors */
    TMXTile(unsigned TileID, std::unordered_map<std::string, std::string> const& propertiesMap);
    ~TMXTile() noexcept;

    /* Getter functions */
    unsigned getTileID() const noexcept;
    std::string getProperty(std::string const& propertyName) noexcept;

    /* Debug functions */
    void printData();

private:
    /* TMXTile variables */
    unsigned m_TileID;

    /* User-defined properties */
    std::unordered_map<std::string, std::string> m_propertiesMap;
};