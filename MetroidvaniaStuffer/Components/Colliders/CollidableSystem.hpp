//
//  CollidableSystem.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/15/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef CollidableSystem_hpp
#define CollidableSystem_hpp

#include <vector>
#include <memory>
#include <set>

#include "Object.hpp"
#include "QuadTree.hpp"
#include "Bitmask.hpp"

class CollidableSystem
{
public:
    CollidableSystem();
    
    void add(std::vector<std::shared_ptr<Object>>& objects);
    void processRemovals();
    void update();
    
private:
    void resolve();
    void processCollisions(std::vector<std::shared_ptr<Object>>& first, std::vector<std::shared_ptr<Object>>& second);
    
    // This is used to store collision layer data i.e. which layers can collide.
    std::map<CollisionLayer, BitMask> collisionLayers;

    // The collision system stores all collidables along with their layer.
    std::map<CollisionLayer, std::vector<std::shared_ptr<CBoxCollider>>> collidables;
    
    // The quadtree stores the collidables in a spatial aware structure.
    QuadTree collisionTree;
};

#endif /* CollidableSystem_hpp */
