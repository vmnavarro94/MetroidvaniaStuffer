//
//  DrawableSystem.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/8/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "DrawableSystem.hpp"

void DrawableSystem::add(std::vector<std::shared_ptr<Object> > &object)
{
    for(auto& obj: object)
    {
        add(obj);
    }
    sort();
}

void DrawableSystem::add(std::shared_ptr<Object> object)
{
    std::shared_ptr<CDrawable> draw = object->getDrawable();
    
    if(draw)
    {
        drawables.emplace_back(object);
    }
}

void DrawableSystem::sort()
{
    std::sort(drawables.begin(), drawables.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b) -> bool
    {
        return a->getDrawable()->getSortOrder() < b->getDrawable()->getSortOrder();
    });
}

void DrawableSystem::draw(Window &window)
{
    for (auto& drawable : drawables)
    {
        drawable->draw(window);
    }
}

void DrawableSystem::processRemovals()
{
    auto objIterator = drawables.begin();
    while(objIterator != drawables.end())
    {
        auto obj = *objIterator;
        
        if(obj->isQueuedForRemoval())
        {
            objIterator = drawables.erase(objIterator);
        }
        else
        {
            objIterator++;
        }
    }
}
