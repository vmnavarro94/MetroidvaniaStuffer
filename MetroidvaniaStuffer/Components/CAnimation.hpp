//
//  CAnimation.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/3/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef CAnimation_hpp
#define CAnimation_hpp

#include "Component.hpp"
#include "Animation.hpp"
#include "CSprite.hpp"

enum class AnimationState
{
    None,
    Idle,
    Walk
};

class CAnimation: public Component
{
public:
    CAnimation(Object* owner);
    
    void awake() override;
    void update(float deltaTime) override;
    
    // Add animation to object.
    void addAnimation(AnimationState state,
            std::shared_ptr<Animation> animation);
    
    void setAnimationState(AnimationState state);
    
    const AnimationState& getAnimationState() const;
    
    void setAnimationDirection(FacingDirection dir);
    
private:
    std::shared_ptr<CSprite> sprite;
    std::map<AnimationState, std::shared_ptr<Animation>> animations;
    
    // We store a reference to the current animation so we
    // can quickly update and draw it.
    std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
};

#endif /* CAnimation_hpp */
