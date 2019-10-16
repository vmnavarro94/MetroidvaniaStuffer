//
//  BitMask.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef BitMask_hpp
#define BitMask_hpp

#include<stdint.h>

class BitMask
{
public:
    BitMask();
    
    BitMask(uint32_t bits);
    
    ///Overrides this bitmask
    void setMask(BitMask& other);
    
    ///Returns binary representation of bitmask
    uint32_t getMask() const;
    
    // Returns true if bit at pos = 1, else false.
    bool getBit(int pos) const; 
    
    ///Set bit at specified postiion to 1 or 0
    void setBit(int pos, bool bitVal);
    
    ///Set bit at specified postiion to 1
    void setBit(int pos);
    
    ///Set bit at specified postiion to 0
    void clearBit(int pos);
    
    ///Set all bits to 0
    void clear();
    
private:
    uint32_t bits;
};

#endif /* BitMask_hpp */
