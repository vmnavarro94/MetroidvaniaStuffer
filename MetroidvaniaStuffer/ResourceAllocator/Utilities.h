//
//  Utilities.h
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/3/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Utilities_h
#define Utilities_h

class Utilities
{
public:
    // Used answers from:
    // https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
    //TODO: not robust. Only correctly handles whole positive numbers.
    static inline bool isInteger(const std::string & s)
    {
        if (s.empty()
            || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        {
            return false;
        }
        
        char * p;
        strtol(s.c_str(), &p, 10);
        return (*p == 0);
    }
    
};

#endif /* Utilities_h */
