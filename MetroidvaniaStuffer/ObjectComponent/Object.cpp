//
//  Object.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "Object.hpp"

Object::Object()
    :queuedForRemoval(false)
{
    transform = addComponent<CTransform>();
    instanceId = addComponent<CInstanceId>();
}

//Loop the components and call its methods
//Loop backwards as the component may change during the update or draw methods

void Object::awake()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->awake();
    }
}

void Object::start()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->start();
    }
}

void Object::update(float deltaTime)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->update(deltaTime);
    }
}

void Object::lateUpdate(float deltaTime)
{
    for (int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->lateUpdate(deltaTime);
    }
}

void Object::draw(Window &window)
{
    drawable->draw(window);
}

void Object::queueForRemoval()
{
    queuedForRemoval = true;
}

bool Object::isQueuedForRemoval()
{
    return queuedForRemoval;
}

std::shared_ptr<CDrawable> Object:: getDrawable()
{
    return drawable;
}
