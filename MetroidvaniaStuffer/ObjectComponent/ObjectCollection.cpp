//
//  ObjectCollection.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "ObjectCollection.hpp"

void ObjectCollection::update(float deltaTime)
{
    for(auto& obj : objects)
    {
        obj->update(deltaTime);
    }
    collidables.update();
}

void ObjectCollection::lateUpdate(float deltaTime)
{
    for(auto& obj : objects)
    {
        obj->lateUpdate(deltaTime);
    }
}

void ObjectCollection::draw(Window& window)
{
    drawables.draw(window);
}

void ObjectCollection::add(std::shared_ptr<Object> object)
{
    newObjects.push_back(object);
}

void ObjectCollection::add(std::vector<std::shared_ptr<Object>>& otherObjects)
{
    newObjects.insert(newObjects.end(), otherObjects.begin(), otherObjects.end());
}

void ObjectCollection::processNewObjects()
{
    if (newObjects.size() > 0)
    {
        for (const auto& obj : newObjects)
        {
            obj->awake();
        }
        
        for (const auto& obj : newObjects)
        {
            obj->start();
        }
       
        objects.insert(objects.end(), newObjects.begin(), newObjects.end());
        drawables.add(newObjects);
        collidables.add(newObjects);

        newObjects.clear();
    }
}

void ObjectCollection::processRemovals()
{
    bool removed = false;
    auto objIterator = objects.begin();
    while (objIterator != objects.end())
    {
        auto obj = *objIterator;
        
        if (obj->isQueuedForRemoval())
        {
            objIterator = objects.erase(objIterator);
            removed = true;
        }
        else
        {
            ++objIterator;
        }
    }
    
    if(removed)
    {
        drawables.processRemovals();
        collidables.processRemovals();
    }
}
