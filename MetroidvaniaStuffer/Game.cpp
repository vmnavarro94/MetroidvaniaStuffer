//
//  Game.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "Game.hpp"
#include <string>
#include <iostream>

Game::Game()
:window("Metroidvania Stuffer")
{
    std::shared_ptr<SceneSplashScreen> splashScreen =
         std::make_shared<SceneSplashScreen>(workingDir,
                                             sceneStateMachine,
                                             window,
                                             textureAllocator);
    
    std::shared_ptr<SceneGame> gameScene =
        std::make_shared<SceneGame>(workingDir, textureAllocator);
       
    unsigned int splashScreenID = sceneStateMachine.add(splashScreen);
    unsigned int gameSceneID = sceneStateMachine.add(gameScene);
    
    splashScreen->setSwitchScene(gameSceneID);
    
    sceneStateMachine.switchTo(splashScreenID);
    
    deltaTime = clock.restart().asSeconds();
}

void Game::update()
{
    window.update();
    sceneStateMachine.update(deltaTime);
}

void Game::lateUpdate()
{
    sceneStateMachine.lateUpdate(deltaTime);
}

void Game::draw()
{
    window.beginDraw();
    
    sceneStateMachine.draw(window);
    
    window.endDraw();
}

bool Game::isRunning() const
{
    return window.isOpen();
}

void Game::calculateDeltaTime()
{
    deltaTime = clock.restart().asSeconds();
}

void Game::captureInput()
{
    sceneStateMachine.processInput();
}

