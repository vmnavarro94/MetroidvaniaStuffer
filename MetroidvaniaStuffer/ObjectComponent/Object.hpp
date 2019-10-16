//
//  Object.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Window.hpp"
#include "Component.hpp"
#include <vector>
#include "CTransform.hpp"
#include "CDrawable.hpp"
#include "CInstanceId.hpp"

class Object
{
public:
    
    Object();
    
    //Awake method is called when objects are created.
    //Use to ensure required components are present
    void awake();
    
    //Start method is called after awake method.
    //use this to initiallize variables.
    void start();
    
    void update(float deltaTime);
    void lateUpdate(float deltaTime);
    void draw(Window& window);
    
    template<typename T> std::shared_ptr<T> addComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        //TODO: allow us to add more than one component, implement getcomponents
        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        
        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        
        components.push_back(newComponent);
        
        if (std::dynamic_pointer_cast<CDrawable>(newComponent))
        {
            drawable = std::dynamic_pointer_cast<CDrawable>(newComponent);
        }
        
        return newComponent;
    }
    
    template<typename T> std::shared_ptr<T> getComponent()
    {
        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        
        return nullptr;
    }
    
    std::shared_ptr<CDrawable> getDrawable();
    
    bool isQueuedForRemoval();
    void queueForRemoval();
    
    //Transform component is default on any object
    std::shared_ptr<CTransform> transform;
    
    std::shared_ptr<CInstanceId> instanceId;
    
private:
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<CDrawable> drawable;
    bool queuedForRemoval;
};

#endif /* Object_hpp */
