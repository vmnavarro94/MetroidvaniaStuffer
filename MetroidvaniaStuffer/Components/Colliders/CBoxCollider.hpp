//
//  CBoxCollider.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/9/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef CBoxCollider_hpp
#define CBoxCollider_hpp

#include "Component.hpp"
#include "CCollider.hpp"
#include <math.h>

class CBoxCollider : public CCollider
{
public:
    CBoxCollider(Object* owner);
    
    MainFold intersects(std::shared_ptr<CCollider> other) override;
    void resolveOverlap(const MainFold& m) override;
    
    void setCollidable(const sf::FloatRect& rect);
    const sf::FloatRect& getCollidable();
    
private:
    void setPosition();
    
    sf::FloatRect AABB;
    sf::Vector2f offset;
};

#endif /* CBoxCollider_hpp */
