//
//  Animation.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/3/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <vector>

struct FrameData
{
    int id;                     //Texture id (retrieved from texture allocator)
    int x;                      //x position of the sprite in the texture
    int y;                      //y position of the sprite in the texture
    int width;                  //Width of the sprite
    int height;                 //Height of the sprite
    float displayTimeSeconds;   //How long to display the frame
};

enum class FacingDirection
{
    None,
    Left,
    Right
};

class Animation
{
public:
    Animation(FacingDirection direction);
    
    FacingDirection getDirection() const;
    void setDirection(FacingDirection dir);
    
    void addFrame(int textureId, int x, int y, int width, int height, float frameTime);
    const FrameData* getCurrentFrame() const;
    
    bool updateFrame(float deltaTime);
    
    void reset();
    
private:
    void incrementFrame();
    
    // Stores all frames for our animation.
    std::vector<FrameData> frames;
    
    // Current frame.
    int currentFrameIndex;
    
    // We use this to decide when to transition to the next frame.
    float currentFrameTime;
    
    FacingDirection direction;
};

#endif /* Animation_hpp */
