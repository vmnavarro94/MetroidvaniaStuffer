//
//  CDrawable.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/8/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef CDrawable_hpp
#define CDrawable_hpp

#include <SFML/Graphics.hpp>
#include "Window.hpp"

class CDrawable
{
public:
    CDrawable();
    virtual ~CDrawable();
    
    virtual void draw(Window& window) = 0;
    
    void setSortOrder(int order);
    int getSortOrder();
    
private:
    int sortOrder;
};

#endif /* CDrawable_hpp */
