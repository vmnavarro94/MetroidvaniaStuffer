//
//  CBoxCollider.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/9/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "CBoxCollider.hpp"
#include "Object.hpp"

CBoxCollider::CBoxCollider(Object* owner)
: CCollider(owner), offset(sf::Vector2f(0.f, 0.f)){}

void CBoxCollider::setCollidable(const sf::FloatRect &rect)
{
    AABB = rect;
    setPosition();
}

const sf::FloatRect& CBoxCollider::getCollidable()
{
    setPosition();
    return AABB;
}

void CBoxCollider::setPosition()
{
    const sf::Vector2f& pos = owner->transform->getPosition();
    
    AABB.left = pos.x - (AABB.width / 2) + offset.x;
    AABB.top = pos.y - (AABB.height / 2) + offset.y;
}

MainFold CBoxCollider::intersects(std::shared_ptr<CCollider> other)
{
    MainFold m;
    m.colliding = false; //Not colliding by default
    
    std::shared_ptr<CBoxCollider> boxCollider = std::dynamic_pointer_cast<CBoxCollider>(other);
    
    if(boxCollider)
    {
        const sf::FloatRect& rect1 = getCollidable();
        const sf::FloatRect& rect2 = boxCollider->getCollidable();
        
        if(rect1.intersects(rect2))
        {
            m.colliding = true;
            m.other  = &rect2;
        }
    }
    
    return m;
}

void CBoxCollider::resolveOverlap(const MainFold &m)
{
    auto transform = owner -> transform;
    
    if(transform->isStatic())
    {
        return;
    }
    
    const sf::FloatRect& rect1 = getCollidable();
    const sf::FloatRect* rect2 = m.other;
    
    float resolve = 0;
    float xDiff = (rect1.left + (rect1.width * 0.5f)) - (rect2->left + (rect2->width * 0.5f));
    float yDiff = (rect1.top + (rect1.height * 0.5f)) - (rect2->top + (rect2->height * 0.5f));
    
    if(fabs(xDiff) > fabs(yDiff))
    {
        if(xDiff > 0) //Colliding on left
        {
            // Add a positive x value to move the object to the right.
            resolve = (rect2->left + rect2->width) - rect1.left;
        }
        else // Colliding on the right
        {
            // We add a negative x value to move the object to the left.
            resolve = -((rect1.left + rect1.width) - rect2->left);
        }
        
        transform->addPosition(resolve, 0);
    }
    else
    {
        if (yDiff > 0) // Colliding above.
        {
            // Add a positive y value to move the object down.
            resolve = (rect2->top + rect2->height) - rect1.top;
        }
        else // Colliding below
        {
            // Add a negative y value to move the object up.
            resolve = -((rect1.top + rect1.height) - rect2->top);
        }
        
        transform->addPosition(0, resolve);
    }
}
