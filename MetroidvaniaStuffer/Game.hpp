//
//  Game.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "WorkingDirectory.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "SceneStateMachine.hpp"
#include "SceneSplashScreen.hpp"
#include "SceneGame.hpp"

class Game
{
public:
    Game();
    
    void captureInput();
    void update();
    void lateUpdate();
    void draw();
    void calculateDeltaTime();
    
    bool isRunning() const;
    
private:
    Window window;
    WorkingDirectory workingDir;
    
    sf::Clock clock;
    float deltaTime;
    
    SceneStateMachine sceneStateMachine;
    
    ResourceAllocator<sf::Texture> textureAllocator;
};
#endif /* Game_hpp */
