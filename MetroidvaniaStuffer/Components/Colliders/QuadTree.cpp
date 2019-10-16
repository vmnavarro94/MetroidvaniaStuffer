//
//  QuadTree.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/14/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "QuadTree.hpp"

QuadTree::QuadTree()
    : QuadTree(5, 5, 0, {0.f, 0.f, 1920, 1080}, nullptr){}

QuadTree::QuadTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, QuadTree* parent)
    : maxObjects(maxObjects), maxLevels(maxLevels), level(level), bounds(bounds), parent(parent) {}

void QuadTree::insert(std::shared_ptr<CBoxCollider> object)
{
    if (children[0] != nullptr)
    {
        int indexToPlaceObj = getChildIndexForObjects(object->getCollidable());
        
        if(indexToPlaceObj != thisThree)
        {
            children[indexToPlaceObj]->insert(object);
            return;
        }
        
    }
    
    objects.emplace_back(object);
    
    if(objects.size() > maxObjects && level > maxLevels && children[0] == nullptr)
    {
        split();
        
        auto objIterator = objects.begin();
        while(objIterator != objects.end())
        {
            auto obj = *objIterator;
            int indexToPlaceObj = getChildIndexForObjects(obj->getCollidable());
            
            if(indexToPlaceObj != thisThree)
            {
                children[indexToPlaceObj]->insert(object);
                objIterator = objects.erase(objIterator);
            }
            else
            {
                objIterator++;
            }
            
        }
    }
}

void QuadTree::remove(std::shared_ptr<CBoxCollider> object)
{
    int index = getChildIndexForObjects(object->getCollidable());
    
    if (index == thisThree || children[index] == nullptr)
    {
        for(int i=0; i < objects.size(); i++)
        {
            if(objects.at(i)->owner->instanceId->get() == object->owner->instanceId->get())
            {
                objects.erase(objects.begin() + i);
                break;
            }
        }
    }
    else
    {
        return children[index]->remove(object);
    }
}

void QuadTree::clear()
{
    objects.clear();
    
    for(int i=0; i < 4; i++)
    {
        if(children[i] != nullptr)
        {
            children[i]->clear();
            children[i] = nullptr;
        }
    }
}

std::vector<std::shared_ptr<CBoxCollider>> QuadTree::search(const sf::FloatRect& area)
{
    std::vector<std::shared_ptr<CBoxCollider>> possibleOverlaps;
    search(area, possibleOverlaps);
    
    std::vector<std::shared_ptr<CBoxCollider>> returnList;
    
    for(auto collider : possibleOverlaps)
    {
        if(area.intersects(collider->getCollidable()))
        {
            returnList.emplace_back(collider);
        }
        
    }
    
    return returnList;
}

void QuadTree::search(const sf::FloatRect &area, std::vector<std::shared_ptr<CBoxCollider> > &overlappingObjects)
{
    overlappingObjects.insert(overlappingObjects.end(), objects.begin(), objects.end());
    
    if(children[0] != nullptr)
    {
        int index = getChildIndexForObjects(area);
        
        if(index == thisThree)
        {
            for(int i = 0; i < 4; i++)
            {
                if(children[i]->getBounds().intersects(area))
                {
                    children[i]->search(area, overlappingObjects);
                }
            }
        }
        else
        {
            children[index]->search(area, overlappingObjects);
        }
    }
}

const sf::FloatRect& QuadTree::getBounds() const
{
    return bounds;
}

int QuadTree::getChildIndexForObjects(const sf::FloatRect &objectBounds)
{
    int index = -1;
    
    double verticalDividingLine = bounds.left + bounds.width * 0.5f;
    double horizontalDividingLine = bounds.top + bounds.height * 0.5f;
    
    bool north = objectBounds.top < horizontalDividingLine
        && (objectBounds.height + objectBounds.top < horizontalDividingLine);
    bool south = objectBounds.top > horizontalDividingLine;
    bool west = objectBounds.left < verticalDividingLine
        && (objectBounds.left + objectBounds.width < verticalDividingLine);
    bool east = objectBounds.left > verticalDividingLine;
    
    if(east)
    {
        if(north)
        {
            index = childNE;
        }
        else if(south)
        {
            index = childSE;
        }
    }
    else if(west)
    {
        if(north)
        {
            index = childNW;
        }
        else if(south)
        {
            index = childSW;
        }
    }
    
    return index;
}

void QuadTree::split()
{
    const int childWidth = bounds.width / 2;
    const int childHeight = bounds.height / 2;
    
    children[childNE] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left + childWidth, bounds.top, childWidth, childHeight), this);
    children[childNW] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left, bounds.top, childWidth, childHeight), this);
    children[childSW] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left, bounds.top + childHeight, childWidth, childHeight), this);
    children[childSE] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left + childWidth, bounds.top + childHeight, childWidth, childHeight), this);
}

