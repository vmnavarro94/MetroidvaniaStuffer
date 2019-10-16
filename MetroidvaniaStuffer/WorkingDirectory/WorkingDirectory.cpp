//
//  WorkingDirectory.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//
#include "WorkingDirectory.hpp"

WorkingDirectory::WorkingDirectory()
{
    path = "./";

#ifdef MACOS  
    // Change the default working directory to that of
    // the XCode resource path on MacOS.
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL =
        CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (CFURLGetFileSystemRepresentation(
        resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        CFRelease(resourcesURL);
        chdir(path);
    }
    
#endif
}
