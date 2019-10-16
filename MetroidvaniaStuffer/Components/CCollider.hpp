//
//  CCollider.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/9/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef CCollider_hpp
#define CCollider_hpp

#include<memory>
#include <SFML/Graphics.hpp>
#include "Component.hpp"

//Enum to be used when defining collision layers
enum class CollisionLayer
{
    Default = 1,    //bit 0
    Player = 2,     //bit 1
    Tile = 3        //bit 2
};

struct MainFold
{
    bool colliding = false;
    const sf::FloatRect* other;
};

class CCollider : public Component
{
public:
    CCollider(Object* owner);
    ~CCollider();
    
    virtual MainFold intersects(std::shared_ptr<CCollider> other) = 0;
    virtual void resolveOverlap(const MainFold& m) = 0;
    
    CollisionLayer getLayer() const;
    void setLayer(CollisionLayer layer);
    
private:
    CollisionLayer layer;
};

#endif /* CCollider_hpp */
