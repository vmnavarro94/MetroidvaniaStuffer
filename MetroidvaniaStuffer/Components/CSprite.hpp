//
//  CSprite.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef CSprite_hpp
#define CSprite_hpp

#include "Component.hpp"
#include "CTransform.hpp"
#include "ResourceAllocator.hpp"
#include "CDrawable.hpp"

class CSprite: public Component, public CDrawable
{
public:
    CSprite(Object* owner);
    
    //Loads a sprite from a file
    void load(const std::string& path);
    
    //Overloaded method that accepts texture id
    void load(int id);
    
    void setTextureAllocator(ResourceAllocator<sf::Texture>* allocator);
    
    //Overrided draw method to draw the sprite
    void draw(Window& window) override;
    
    //Update position of the sprite
    void lateUpdate(float deltaTime) override;
    
    void setTextureRect(int x, int y, int width, int height);
    void setTextureRect(const sf::IntRect& rect);
    
    void setScale(float x, float y);
    
private:
    ResourceAllocator<sf::Texture>* allocator;
    sf::Sprite sprite;
    int currentTextureID;
};

#endif /* CSprite_hpp */
