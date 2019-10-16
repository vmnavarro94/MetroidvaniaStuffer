//
//  Scene.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Window.hpp"
class Scene
{
public:
    // Called when scene initially created. Called once.
    virtual void onCreate() = 0;
    
    // Called when scene destroyed. Called at most once (if a scene
    // is not removed from the game, this will never be called).
    virtual void onDestroy() = 0;
    
    // Called whenever a scene is transitioned into. Can be
    // called many times in a typical game cycle.
    virtual void onActivate() {};
    
    // Called whenever a transition out of a scene occurs.
    // Can be called many times in a typical game cycle.
    virtual void onDeactivate() {};
    
    // The below functions can be overridden as necessary in our scenes.
    virtual void processInput() {};
    virtual void update(float deltaTime) {};
    virtual void lateUpdate(float deltaTime) {};
    virtual void draw(Window& window) {};
};
#endif /* Scene_hpp */
