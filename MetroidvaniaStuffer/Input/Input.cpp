//
//  Input.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "Input.hpp"

void Input::update()
{
    lastFrameKeys.setMask(thisFrameKeys);
    
    thisFrameKeys.setBit((int) Key::Left,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::A)));
    thisFrameKeys.setBit((int)Key::Right,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::D)));
    thisFrameKeys.setBit((int)Key::Up,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::W)));
    thisFrameKeys.setBit((int)Key::Down,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::S)));
    thisFrameKeys.setBit((int)Key::Exit),
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

// Return true if the specified key is currently being pressed.
bool Input::isKeyPressed(Key keyCode)
{
    return thisFrameKeys.getBit((int)keyCode);
}

// Returns true if the key was just pressed
// (i.e. registered as pressed this frame but not the previous).
bool Input::isKeyDown(Key keycode)
{
    bool lastFrame = lastFrameKeys.getBit((int)keycode);
    bool thisFrame = thisFrameKeys.getBit((int)keycode);
    
    return thisFrame && !lastFrame;
}

// Returns true if the key was just released (i.e. registered as
// pressed last frame but not the current frame).
bool Input::isKeyUp(Key keycode)
{
    bool lastFrame = lastFrameKeys.getBit((int)keycode);
    bool thisFrame = thisFrameKeys.getBit((int)keycode);
    
    return !thisFrame && lastFrame;
}

