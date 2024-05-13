#pragma once
#include <vector>
#include <unordered_map>

class TMXTileLayer final
{
public:
    /* Class constructors & destructors */
    TMXTileLayer(std::string const& name, unsigned width, unsigned height,
        std::unordered_map<std::string, std::string> const& layerProperties,
        std::vector<std::vector<unsigned>> const& tileVector);
    ~TMXTileLayer() noexcept;

    /* Getter functions  */
    unsigned getWidth() const noexcept;
    unsigned getHeight() const noexcept;
    std::string getName() const noexcept;
    std::string getProperty(std::string const& propertyName) noexcept;
    std::vector<std::vector<unsigned>> getTiles() const noexcept;

    /* Debug functions */
    void printData();

private:
    /* Layer variables */
    unsigned m_width, m_height;
    std::string m_name;
    std::vector<std::vector<unsigned>> m_tileVector;
    std::unordered_map<std::string, std::string> m_layerProperties;
};