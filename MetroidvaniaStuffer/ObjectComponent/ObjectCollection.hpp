//
//  ObjectCollection.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef ObjectCollection_hpp
#define ObjectCollection_hpp

#include <memory>
#include <vector>

#include "Object.hpp"
#include "DrawableSystem.hpp"

class ObjectCollection
{
public:
    void add(std::shared_ptr<Object> object);
    void add(std::vector<std::shared_ptr<Object>>& otherObjects);
    
    void update(float deltaTime);
    void lateUpdate(float deltaTime);
    void draw(Window& window);
    
    //This method will be responsible for moving objects added that frame from a temporary new
    //object collection to the main object collection so they are updated, drawn etc.
    void processNewObjects();
    
    void processRemovals();
    
private:
    std::vector<std::shared_ptr<Object>> objects;
    
    //buffer for new objects that are going to be moved to objects collection
    std::vector<std::shared_ptr<Object>> newObjects;
    
    DrawableSystem drawables;
};

#endif /* ObjectCollection_hpp */
