//
//  Input.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <SFML/Graphics.hpp>
#include "Bitmask.hpp"

class Input
{
public:
    
    enum class Key
    {
        None = 0,
        Left = 1,
        Right = 2,
        Up = 3,
        Down = 4,
        Exit = 5
    };
    
    ///Returns true if a key is pressed
    bool isKeyPressed(Key keyCode);
    
    ///Returns true if a key was just pressed
    bool isKeyDown(Key keyCode);
    
    ///Returns true is a key was just released
    bool isKeyUp(Key keycode);
    
    void update();
    
private:
    
    BitMask thisFrameKeys;
    BitMask lastFrameKeys;
    
};

#endif /* Input_hpp */
