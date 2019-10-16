//
//  Tile.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/3/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Tile_h
#define Tile_h

#include "ResourceAllocator.hpp"
#include <SFML/Graphics.hpp>

//stores common tile data
struct TileInfo
{
    TileInfo():tileId(-1){}
    
    TileInfo(int textureId, unsigned int tileId, sf::IntRect textureRect)
        : textureId(textureId), tileId(tileId),textureRect(textureRect){}
    
    int tileId;
    int textureId;
    sf::IntRect textureRect;
};

struct Tile
{
    std::shared_ptr<TileInfo> properties;
    int x;
    int y;
};

#endif /* Tile_hpp */
