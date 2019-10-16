//
//  SceneGame.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "SceneGame.hpp"
#include "CKeyboardMovement.hpp"

SceneGame::SceneGame(WorkingDirectory& workingDir,
                 ResourceAllocator<sf::Texture>& textureAllocator)
: workingDir(workingDir), textureAllocator(textureAllocator), mapParser(textureAllocator)
{
    
}

void SceneGame::onCreate()
{
    std::shared_ptr<Object> player = std::make_shared<Object>();
    
    //Add components
    auto sprite = player->addComponent<CSprite>();
    sprite->setTextureAllocator(&textureAllocator);
    
    auto movement = player->addComponent<CKeyboardMovement>();
    movement->setInput(&input);
    
    auto animation = player->addComponent<CAnimation>();
    
    int vikingTextureId = textureAllocator.add(workingDir.get() + "viking.png");
    
    const int frameWidth = 165;
    const int frameHeight = 145;
    
    std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>(FacingDirection::Right);
    
    const float idleAnimFrameSeconds = 0.2f;
    
    idleAnimation->addFrame(vikingTextureId, 600, 0, frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->addFrame(vikingTextureId, 800, 0, frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->addFrame(vikingTextureId, 0, 145, frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->addFrame(vikingTextureId, 200, 145, frameWidth, frameHeight, idleAnimFrameSeconds);
    
    animation->addAnimation(AnimationState::Idle, idleAnimation);
    
    std::shared_ptr<Animation> walkAnimation =
        std::make_shared<Animation>(FacingDirection::Right);
    const float walkAnimFrameSeconds = 0.15f;
    
    walkAnimation->addFrame(vikingTextureId, 600, 290,
                            frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->addFrame(vikingTextureId, 800, 290,
                            frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->addFrame(vikingTextureId, 0, 435,
                            frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->addFrame(vikingTextureId, 200, 435,
                            frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->addFrame(vikingTextureId, 400, 435,
                            frameWidth, frameHeight, walkAnimFrameSeconds);
    
    animation->addAnimation(AnimationState::Walk, walkAnimation);
    
    objects.add(player);
    
    sf::Vector2i mapOffset(-400, 128);
    std::vector<std::shared_ptr<Object>> levelTiles = mapParser.parse(workingDir.get() + "testMap.tmx", mapOffset);
    
    objects.add(levelTiles);
}

void SceneGame::onDestroy()
{
    
}

void SceneGame::processInput()
{
    input.update();
}

void SceneGame::update(float deltaTime)
{
    objects.processRemovals();
    objects.processNewObjects();
    
    objects.update(deltaTime);
}

void SceneGame::lateUpdate(float deltaTime)
{
    objects.lateUpdate(deltaTime);
}

void SceneGame::draw(Window &window)
{
    objects.draw(window);
}
