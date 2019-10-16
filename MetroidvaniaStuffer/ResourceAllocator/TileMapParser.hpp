//
//  TileMapParser.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/3/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef TileMapParser_hpp
#define TileMapParser_hpp

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <sstream>

#include "rapidxml.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "Tile.h"
#include "Object.hpp"
#include "CSprite.hpp"
#include "Utilities.h"
#include "CBoxCollider.hpp"

using namespace rapidxml;

struct TileSheetData
{
    // The texture id will be retrieved by using our texture allocator.
    int textureId; // The id of the tile sets texture.
    sf::Vector2u imageSize; // The size of the texture.
    int columns; // How many columns in the tile sheet.
    int rows; // How many rows in the tile sheet.
    sf::Vector2u tileSize; // The size of an individual tile.
};

struct Layer
{
    std::vector<std::shared_ptr<Tile>> tiles;
    bool isVisible;
};

// Stores layer names with layer.
using MapTiles = std::map<std::string, std::shared_ptr<Layer>>;
// Stores the different tile types that can be used.
using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;
using TileSheets = std::map<int, std::shared_ptr<TileSheetData>>;


class TileMapParser
{
public:
    TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator);
    
    std::vector<std::shared_ptr<Object>> parse(const std::string& file, sf::Vector2i offset);
    
private:
    std::shared_ptr<TileSheets> buildTileSheetData(xml_node<>* rootNode);
    std::shared_ptr<MapTiles> buildMapTiles(xml_node<>* rootNode);
    std::pair<std::string, std::shared_ptr<Layer>> buildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheets> tileSheets);
    
    ResourceAllocator<sf::Texture>& textureAllocator;
};

#endif /* TileMapParser_hpp */
