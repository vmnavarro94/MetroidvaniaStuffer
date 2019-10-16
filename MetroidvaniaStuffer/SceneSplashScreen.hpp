//
//  SceneSplashScreen.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef SceneSplashScreen_hpp
#define SceneSplashScreen_hpp

#include <SFML/Graphics.hpp>
#include "SceneStateMachine.hpp"
#include "WorkingDirectory.hpp"
#include "ResourceAllocator.hpp"

class SceneSplashScreen: public Scene
{
public:
    SceneSplashScreen(WorkingDirectory& workingDir, SceneStateMachine& sceneStateMachine,
                      Window& window, ResourceAllocator<sf::Texture>& textureAllocator);
    void onCreate() override;
    void onDestroy() override;
    void onActivate() override;
    
    void setSwitchScene(unsigned int id);
    
    void update(float deltaTime) override;
    void draw(Window& window) override;
    
private:
    sf::Sprite splashSprite;
    
    ResourceAllocator<sf::Texture>& textureAllocator;
    
    WorkingDirectory& workingDir;
    SceneStateMachine& sceneStateMachine;
    Window& window;
    
    //This scene will be showed only for certain time
    float showForSeconds;
    
    //How long has the scene been visible
    float currentSeconds;
    
    //The scene we want to trancition to when this scene finishes
    unsigned int switchToState;
};

#endif /* SceneSplashScreen_hpp */
