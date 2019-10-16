//
//  TileMapParser.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/3/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "TileMapParser.hpp"
#include <string>
#include <fstream>
#include <stdexcept>

TileMapParser::TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator)
: textureAllocator(textureAllocator){}

std::vector<std::shared_ptr<Object>>
TileMapParser::parse(const std::string &file, sf::Vector2i offset)
{
    char* fileLoc = new char[file.size() + 1];
    
    //TODO: make multi format version of string copy
#ifdef MACOS
    strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
    strcpy_s(fileLoc, file.size() + 1, file.c_str());
#endif
    
    //TODO: error checking - check file exists before attempting open.
    rapidxml::file<> xmlFile(fileLoc);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<>* rootNode = doc.first_node("map");
    
    // Loads tile layers from XML.
    std::shared_ptr<MapTiles> map = buildMapTiles(rootNode);
    
    // We need these to calculate the tiles position in world space
    int tileSizeX = std::atoi(rootNode->first_attribute("tilewidth")->value());
    int tileSizeY = std::atoi(rootNode->first_attribute("tileheight")->value());
    int mapsizeX = std::atoi(rootNode->first_attribute("width")->value());
    int mapsizeY = std::atoi(rootNode->first_attribute("height")->value());
    
    // This will contain all of our tiles as objects.
    std::vector<std::shared_ptr<Object>> tileObjects;
    
    int layerCount = map->size() - 1;
    
    // We iterate through each layer in the tile map
    for (const auto& layer : *map)
    {
        // And each tile in the layer
        for (const auto& tile : layer.second->tiles)
        {
            std::shared_ptr<TileInfo> tileInfo = tile->properties;
            
            std::shared_ptr<Object> tileObject = std::make_shared<Object>();
            
            //TODO: tile scale should be set at the data level.
            const unsigned int tileScale = 3;
            
            if(layer.second->isVisible)
            {
                // Allocate sprite.
                auto sprite = tileObject->addComponent<CSprite>();
                sprite->setTextureAllocator(&textureAllocator);
                sprite->load(tileInfo->textureId);
                sprite->setTextureRect(tileInfo->textureRect);
                sprite->setScale(tileScale, tileScale);
                sprite->setSortOrder(layerCount);
            }
            
            // Calculate world position.
            float x = tile->x * tileSizeX * tileScale + offset.x;
            float y = tile->y * tileSizeY * tileScale + offset.y;
            tileObject->transform->setPosition(x, y);
            
            // Add new tile Object to the collection.
            tileObjects.emplace_back(tileObject);
        }
        layerCount--;
    }
    
    return tileObjects;
}



std::shared_ptr<MapTiles> TileMapParser::buildMapTiles(xml_node<>* rootNode)
{
    std::shared_ptr<TileSheets> tileSheetData = buildTileSheetData(rootNode);
    
    std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();
    
    // We loop through each layer in the XML document.
    for (xml_node<> * node = rootNode->last_node("layer"); node; node = node->previous_sibling("layer"))
    {
        std::pair<std::string, std::shared_ptr<Layer>> mapLayer = buildLayer(node, tileSheetData);
        map->emplace(mapLayer);
    }
    
    return map;
}

std::shared_ptr<TileSheets>
TileMapParser::buildTileSheetData(xml_node<> *rootNode)
{
    TileSheets tileSheets;
    
    for (xml_node<> * tilesheetNode
         = rootNode->first_node("tileset");
         tilesheetNode;
         tilesheetNode = tilesheetNode->next_sibling("tileset"))
    {
        TileSheetData tileSheetData;
        
        //TODO: add error checking to ensure these values actually exist.
        int firstid = std::atoi(tilesheetNode->first_attribute("firstgid")->value());
        tileSheetData.tileSize.x = std::atoi(tilesheetNode->first_attribute("tilewidth")->value());
        tileSheetData.tileSize.y = std::atoi(tilesheetNode->first_attribute("tileheight")->value());
        int tileCount = std::atoi(tilesheetNode->first_attribute("tilecount")->value());
        tileSheetData.columns = std::atoi(tilesheetNode->first_attribute("columns")->value());
        tileSheetData.rows = tileCount / tileSheetData.columns;
        
        xml_node<>* imageNode = tilesheetNode->first_node("image");
        tileSheetData.textureId = textureAllocator.add(std::string(imageNode->first_attribute("source")->value()));
        //TODO: add error checking - we want to output a message if the texture is not found:
        /*
         if(tileSheetData.textureId < 0)
         {
         // Texture not found.
         }
         */
        
        tileSheetData.imageSize.x = std::atoi(imageNode->first_attribute("width")->value());
        tileSheetData.imageSize.y = std::atoi(imageNode->first_attribute("height")->value());
        
        tileSheets.insert(std::make_pair(firstid, std::make_shared<TileSheetData>(tileSheetData)));
        
    }
    
    return std::make_shared<TileSheets>(tileSheets);
}


std::pair<std::string, std::shared_ptr<Layer>>
TileMapParser::buildLayer(xml_node<>* layerNode,
                          std::shared_ptr<TileSheets> tileSheets)
{
    
    TileSet tileSet;
    std::shared_ptr<Layer> layer = std::make_shared<Layer>();
    
    int width = std::atoi(layerNode->first_attribute("width")->value());
    int height = std::atoi(layerNode->first_attribute("height")->value());
    
    xml_node<>* dataNode = layerNode->first_node("data");
    char* mapIndices = dataNode->value();
    
    std::stringstream fileStream(mapIndices);
    
    int count = 0;
    
    std::string line;
    while (fileStream.good())
    {
        std::string substr;
        std::getline(fileStream, substr, ',');
        
        if (!Utilities::isInteger(substr))
        {
            // We remove special characters from the int before parsing
            substr.erase(
                std::remove(substr.begin(), substr.end(), '\r'), substr.end());
            substr.erase(
                std::remove(substr.begin(), substr.end(), '\n'), substr.end());
            
            //TODO: add additional check to confirm that the character removals have worked:
            /*
             if(!Utilities::IsInteger(substr))
             {
             //String is still not integer.
             }
             */
        }
        
        int tileId = std::stoi(substr);
        
        if (tileId != 0)
        {
            auto itr = tileSet.find(tileId);
            if (itr == tileSet.end())
            {
                std::shared_ptr<TileSheetData> tileSheet;
                
                for (auto iter = tileSheets->rbegin(); iter != tileSheets->rend(); ++iter)
                {
                    if(tileId >= iter->first)
                    {
                        // We know the tile belongs to this tileset.
                        tileSheet = iter->second;
                        break;
                    }
                }
                
                if(!tileSheet)
                {
                    //TODO: output error message.
                    continue;
                }
                
                int textureX = tileId % tileSheet->columns - 1;
                int textureY = tileId / tileSheet->columns;
                
                std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(tileSheet->textureId, tileId, sf::IntRect(textureX * tileSheet->tileSize.x, textureY * tileSheet->tileSize.y, tileSheet->tileSize.x, tileSheet->tileSize.y));
                
                itr = tileSet.insert(std::make_pair(tileId, tileInfo)).first;
            }
            
            std::shared_ptr<Tile> tile = std::make_shared<Tile>();
            
            // Bind properties of a tile from a set.
            tile->properties = itr->second;
            tile->x = count % width - 1;
            tile->y = count / width;
            
            
            layer->tiles.emplace_back(tile);
        }
        
        count++;
    }
    
    const std::string layerName = layerNode->first_attribute("name")->value();
    
    bool layerVisible = true;
    xml_attribute<>* visibleAttribute = layerNode->first_attribute("visible");
    if(visibleAttribute) // 2
    {
        layerVisible = std::stoi(visibleAttribute->value());
    }
    layer->isVisible = layerVisible;
    
    return std::make_pair(layerName, layer);
}
