//
//  CTransform.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "CTransform.hpp"

CTransform::CTransform(Object* owner)
    : Component(owner), position(0.f, 0.f), isStaticTransform(false)
{
    
}

void CTransform::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

void CTransform::setPosition(sf::Vector2f pos)
{
    position = pos;
}

void CTransform::addPosition(float x, float y)
{
    position.x += x;
    position.y += y;
}

void CTransform::addPosition(sf::Vector2f pos)
{
    position += pos;
}

void CTransform::setX(float x)
{
    position.x = x;
}

void CTransform::setY(float y)
{
    position.y = y;
}

void CTransform::addX(float x)
{
    position.x += x;
}

void CTransform::addY(float y)
{
    position.y += y;
}

const sf::Vector2f&  CTransform::getPosition() const
{
    return position;
}

void CTransform::setStatic(bool isStatic)
{
    isStaticTransform = isStatic;
}

bool CTransform::isStatic()
{
    return isStaticTransform;
}
