//
//  CAnimation.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/3/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "CAnimation.hpp"
#include "Object.hpp"

CAnimation::CAnimation(Object* owner)
    :Component(owner), currentAnimation(AnimationState::None, nullptr)
{
    
}

void CAnimation::awake()
{
    sprite = owner->getComponent<CSprite>();
}

void CAnimation::update(float deltaTime)
{
    if(currentAnimation.first != AnimationState::None)
    {
        bool newFrame = currentAnimation.second->updateFrame(deltaTime);
        
        if(newFrame)
        {
            const FrameData* data = currentAnimation.second->getCurrentFrame();
            
            sprite->load(data->id); // 1
            
            sprite->setTextureRect(data->x, data->y, data->width, data->height);
        }
    }
}

void CAnimation::addAnimation(AnimationState state, std::shared_ptr<Animation> animation)
{
    auto inserted = animations.insert(std::make_pair(state, animation));
    
    if (currentAnimation.first == AnimationState::None)
    {
        setAnimationState(state);
    }
}

void CAnimation::setAnimationState(AnimationState state)
{
    // We only set an animation of it is not already
    // our current animation.
    if (currentAnimation.first == state)
    {
        return;
    }
    
    auto animation = animations.find(state);
    if (animation != animations.end())
    {
        currentAnimation.first = animation->first;
        currentAnimation.second = animation->second;
        
        currentAnimation.second->reset();
    }
}

const AnimationState& CAnimation::getAnimationState() const
{
    // Returns out current animation state. We can use this
    // to compare the objects current state to a desired state.
    return currentAnimation.first;
}

void CAnimation::setAnimationDirection(FacingDirection dir)
{
    if(currentAnimation.first != AnimationState::None)
    {
        currentAnimation.second->setDirection(dir);
    }
}
