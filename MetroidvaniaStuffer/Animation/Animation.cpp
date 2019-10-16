//
//  Animation.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/3/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "Animation.hpp"

Animation::Animation(FacingDirection direction)
:frames(0), currentFrameIndex(0), currentFrameTime(0), direction(direction)
{
    
}

void Animation::addFrame(int textureId, int x, int y,
                         int width, int height, float frameTime)
{
    FrameData data;
    data.id = textureId;
    data.x = x;
    data.y = y;
    data.width = width;
    data.height = height;
    data.displayTimeSeconds = frameTime;
    
    frames.push_back(data);
}

const FrameData* Animation::getCurrentFrame() const
{
    if(frames.size() > 0)
    {
        return &frames[currentFrameIndex];
    }
    
    return nullptr;
}

bool Animation::updateFrame(float deltaTime)
{
    if(frames.size() > 0)
    {
        currentFrameTime += deltaTime;
        
        if(currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds)
        {
            currentFrameTime = 0.f;
            incrementFrame();
            return true;
        }
    }
    
    return false;
}

void Animation::incrementFrame()
{
    currentFrameIndex = (currentFrameIndex + 1) % frames.size();
}

void Animation::reset()
{
    currentFrameTime = 0.f;
    currentFrameIndex = 0;
}

void Animation::setDirection(FacingDirection dir)
{
    // Makes sure we do not flip the sprite
    // unless its a new direction.
    if(direction != dir)
    {
        direction = dir;
        for(auto& f : frames)
        {
            //To flip a sprite we multiply its width by 1 which inverts the number (if it was
            //positive it becomes negative and if it was negative it becomes positive)
            f.x += f.width;
            f.width *= -1;
        }
    }
}
