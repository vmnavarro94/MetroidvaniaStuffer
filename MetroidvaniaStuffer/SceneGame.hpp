//
//  SceneGame.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/2/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "Scene.hpp"
#include "Input.hpp"
#include "WorkingDirectory.hpp"
#include "Object.hpp"
#include "CSprite.hpp"
#include "ResourceAllocator.hpp"
#include "ObjectCollection.hpp"
#include "CAnimation.hpp"
#include "TileMapParser.hpp"
#include "CBoxCollider.hpp"

class SceneGame: public Scene
{
public:
    SceneGame(WorkingDirectory& workingDir,
              ResourceAllocator<sf::Texture>& textureAllocator);
    
    void onCreate() override;
    void onDestroy() override;
    
    void processInput() override;
    void update(float deltaTime) override;
    void lateUpdate(float deltaTime) override;
    void draw(Window& window) override;
    
private:
    WorkingDirectory& workingDir;
    Input input;
    
    ResourceAllocator<sf::Texture>& textureAllocator;
    
    ObjectCollection objects;
    
    TileMapParser mapParser;
};

#endif /* SceneGame_hpp */
