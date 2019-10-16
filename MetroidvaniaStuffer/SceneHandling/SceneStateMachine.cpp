//
//  SceneStateMachine.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "SceneStateMachine.hpp"

SceneStateMachine::SceneStateMachine()
:scenes(0), currScene(0)
{
    
}

void SceneStateMachine::processInput()
{
    if(currScene)
    {
        currScene->processInput();
    }
}

void SceneStateMachine::update(float deltaTime)
{
    if(currScene)
    {
        currScene->update(deltaTime);
    }
}

void SceneStateMachine::lateUpdate(float deltaTime)
{
    if(currScene)
    {
        currScene->lateUpdate(deltaTime);
    }
}

void SceneStateMachine::draw(Window &window)
{
    if(currScene)
    {
        currScene->draw(window);
    }
}

unsigned int SceneStateMachine::add(std::shared_ptr<Scene> scene)
{
    auto inserted = scenes.insert(std::make_pair(insertedSceneID, scene));
    
    inserted.first->second->onCreate();
    
    return insertedSceneID++;
}

void SceneStateMachine::remove(unsigned int id)
{
    auto it = scenes.find(id);
    
    if(it != scenes.end())
    {
        //If the scene that we are removing is the current scene,
        //we also want to set that to a null ptr so the scene will not update later
        if(currScene == it->second)
        {
            currScene = nullptr;
        }
        
        //Ensure to call onDestroy method of the scene that is being removed
        it->second->onDestroy();
        scenes.erase(it);
    }
}

void SceneStateMachine::switchTo(unsigned int id)
{
    auto it = scenes.find(id);
    if(it != scenes.end())
    {
        if(currScene)
        {
            //If we hace a current scene, we deactivate it
            currScene->onDeactivate();
        }
        //Setting the current scene ensures that it is updated and drawn.
        currScene = it->second;
        
        currScene->onActivate();
    }
}
