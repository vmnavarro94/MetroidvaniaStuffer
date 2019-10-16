//
//  DrawableSystem.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/8/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef DrawableSystem_hpp
#define DrawableSystem_hpp

#include <map>
#include "CDrawable.hpp"
#include "Object.hpp"

class DrawableSystem
{
public:
    void add(std::vector<std::shared_ptr<Object>>& object);
    void processRemovals();
    void draw(Window& window);
    
private:
    void add(std::shared_ptr<Object> object);
    void sort();
    
    std::vector<std::shared_ptr<Object>> drawables;
};

#endif /* DrawableSystem_hpp */
