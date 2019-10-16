//
//  Component.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include "Window.hpp"

class Object;

class Component
{
public:
    Component(Object* owner):owner(owner) {};
    
    virtual void awake() {}
    virtual void start() {}
    virtual void update(float deltaTime) {}
    virtual void lateUpdate(float deltaTime) {}

    Object* owner;
};

#endif /* Component_hpp */
