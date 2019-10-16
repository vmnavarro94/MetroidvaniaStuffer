//
//  WorkingDirectory.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//


#ifndef WorkingDirectory_hpp
#define WorkingDirectory_hpp

#include <string>

#ifdef MACOS
#include "CoreFoundation/CoreFoundation.h"
#endif

class WorkingDirectory
{
public:
    WorkingDirectory();
    
    inline const std::string& get()
    {
        return path;
    }
private:
    std::string path;
};

#endif /* WorkingDirectory_hpp */
