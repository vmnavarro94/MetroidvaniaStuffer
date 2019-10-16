//
//  CollidableSystem.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/15/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "CollidableSystem.hpp"

CollidableSystem::CollidableSystem()
{
    BitMask defaultCollisions;
    defaultCollisions.setBit((int)CollisionLayer::Default);
    collisionLayers.insert(std::make_pair(CollisionLayer::Default, defaultCollisions));
    
    collisionLayers.insert(std::make_pair(CollisionLayer::Tile, BitMask(0)));
    
    BitMask playerCollisions;
    playerCollisions.setBit((int) CollisionLayer::Default);
    playerCollisions.setBit((int) CollisionLayer::Tile);
    collisionLayers.insert(std::make_pair(CollisionLayer::Player, playerCollisions));
}

void CollidableSystem::add(std::vector<std::shared_ptr<Object> > &objects)
{
    for(auto obj : objects)
    {
        auto collider = obj->getComponent<CBoxCollider>();
        if(collider)
        {
            CollisionLayer layer = collider->getLayer();
            
            auto iterator = collidables.find(layer);
            
            if(iterator != collidables.end())
            {
                collidables[layer].push_back(collider);
            }
            else
            {
                std::vector<std::shared_ptr<CBoxCollider>> objs;
                objs.push_back(collider);
                
                collidables.insert(std::make_pair(layer, objs));
            }
        }
    }
}

void CollidableSystem::processRemovals()
{
    for(auto& layer : collidables)
    {
        auto iterator = layer.second.begin();
        while(iterator != layer.second.end())
        {
            if((*iterator)->owner->isQueuedForRemoval())
            {
                iterator = layer.second.erase(iterator);
            }
            else
            {
                iterator++;
            }
        }
    }
}

void CollidableSystem::update()
{
    collisionTree.clear();
    for(auto maps = collidables.begin(); maps != collidables.end(); maps++)
    {
        for(auto collidable : maps->second)
        {
            collisionTree.insert(collidable);
        }
    }
    
    resolve();
}

void CollidableSystem::resolve()
{
    for(auto maps = collidables.begin(); maps != collidables.end(); maps++)
    {
        // If this layer collides with nothing then no need to
        // perform any further checks.
        if(collisionLayers[maps->first].getMask() == 0)
        {
            continue;
        }
        
        for(auto collidable : maps->second)
        {
            // If this collidable is static then no need to check if
            // it's colliding with other objects.
            if (collidable->owner->transform->isStatic())
            {
                continue;
            }
            
            std::vector<std::shared_ptr<CBoxCollider>> collisions = collisionTree.search(collidable->getCollidable());
            
            for(auto collision : collisions)
            {
                // Make sure we do not resolve collisions between the same object.
                if (collidable->owner->instanceId->get()
                    == collision->owner->instanceId->get())
                {
                    continue;
                }
                bool layersCollide =
                    collisionLayers[collidable->getLayer()].getBit(((int)collision->getLayer()));
                
                if(layersCollide)
                {
                    MainFold m = collidable->intersects(collision);
                    
                    if(m.colliding)
                    {
                        if(collision->owner->transform->isStatic())
                        {
                            collidable->resolveOverlap(m);
                        }
                        else
                        {
                            
                            //TODO: How should we handle collisions when both
                            // objects are not static?
                            // We could implement rigidbodies and mass.
                            collidable->resolveOverlap(m);
                        }
                        
                    }
                }
            }
        }
    }
}
