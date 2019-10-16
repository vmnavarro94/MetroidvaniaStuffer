//
//  CSprite.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "CSprite.hpp"
#include "Object.hpp"

CSprite::CSprite(Object* owner)
    :Component(owner), currentTextureID(-1)
{
    
}

void CSprite::load(const std::string &path)
{
    if(allocator)
    {
        int textureID = allocator->add(path);
        
        // Check its not already our current texture.
        if(textureID >= 0 && textureID != currentTextureID)
        {
            currentTextureID = textureID;
            std::shared_ptr<sf::Texture> texture = allocator->get(textureID);
            sprite.setTexture(*texture);
        }
    }
}

void CSprite::load(int id)
{
    if(id >= 0 && id != currentTextureID)
    {
        currentTextureID = id;
        std::shared_ptr<sf::Texture> texture = allocator->get(id);
        sprite.setTexture(*texture);
    }
}

void CSprite::setTextureAllocator(ResourceAllocator<sf::Texture> *allocator)
{
    this->allocator = allocator;
}

void CSprite::draw(Window &window)
{
    window.draw(sprite);
}

void CSprite::lateUpdate(float deltaTime)
{
    sprite.setPosition(owner->transform->getPosition());
}

void CSprite::setTextureRect(int x, int y, int width, int height)
{
    sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void CSprite::setTextureRect(const sf::IntRect &rect)
{
    sprite.setTextureRect(rect);
}

void CSprite::setScale(float x, float y)
{
    sprite.setScale(x, y);
}
