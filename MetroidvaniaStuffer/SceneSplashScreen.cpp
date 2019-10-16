//
//  SceneSplashScreen.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "SceneSplashScreen.hpp"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory& workingDir,
                                     SceneStateMachine& sceneStateMachine, Window& window,
                                     ResourceAllocator<sf::Texture>& textureAllocator)
    : sceneStateMachine(sceneStateMachine), workingDir(workingDir),
                        window(window), switchToState(0), currentSeconds(0.f),
                        showForSeconds(3.f), textureAllocator(textureAllocator)
{
    
}

void SceneSplashScreen::onCreate()
{
    int textureId = textureAllocator.add(workingDir.get() + "SplashTest.png");
    
    if(textureId >= 0)
    {
        std::shared_ptr<sf::Texture> texture = textureAllocator.get(textureId);
        splashSprite.setTexture(*texture);
    }
}

void SceneSplashScreen::onActivate()
{
    //resets the currentSeconds count whenever the scene is activated
    currentSeconds = 0.0f;
}

void SceneSplashScreen::onDestroy()
{
    
}

void SceneSplashScreen::setSwitchScene(unsigned int id)
{
    //Stores the scene id of the scene we will switch to
    switchToState = id;
}

void SceneSplashScreen::update(float deltaTime)
{
    currentSeconds += deltaTime;
    
    if(currentSeconds >= showForSeconds)
    {
        //Switch state
        sceneStateMachine.switchTo(switchToState);
    }
}

void SceneSplashScreen::draw(Window &window)
{
    window.draw(splashSprite);
}
