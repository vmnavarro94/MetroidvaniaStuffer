//
//  CTransform.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef CTransform_hpp
#define CTransform_hpp

#include "Component.hpp"

class CTransform: public Component
{
public:
    CTransform(Object* owner);
    
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f pos);
    
    void addPosition(float x, float y);
    void addPosition(sf::Vector2f pos);
    
    void setX(float x);
    void setY(float y);
    
    void addX(float x);
    void addY(float y);
    
    void setStatic(bool isStatic);
    bool isStatic();
    
    const sf::Vector2f& getPosition() const;
    
private:
    sf::Vector2f position;
    bool isStaticTransform;
};

#endif /* CTransform_hpp */
