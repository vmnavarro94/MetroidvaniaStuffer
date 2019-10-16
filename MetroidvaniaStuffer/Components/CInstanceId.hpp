//
//  CInstanceId.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/14/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef CInstanceId_hpp
#define CInstanceId_hpp

#include "Component.hpp"

class CInstanceId : Component
{
public:
    CInstanceId(Object* owner);
    ~CInstanceId();
    
    int get() const;
    
private:
    static int count;
    int id;
};

#endif /* CInstanceId_hpp */
