//
//  BitMask.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "BitMask.hpp"

BitMask::BitMask() : bits(0) { }

BitMask::BitMask(uint32_t bits) : bits(bits) {}

void BitMask::setMask(BitMask &other)
{
    bits = other.getMask();
}

uint32_t BitMask::getMask() const
{
    return bits;
}

bool BitMask::getBit(int pos) const
{
    return (bits & (1 << pos)) != 0;
}

void BitMask::setBit(int pos, bool bitVal)
{
    if(bitVal)
        setBit(pos);
    else
        clearBit(pos);
}

void BitMask::setBit(int pos)
{
    bits = bits | 1 << pos;
}

void BitMask::clearBit(int pos)
{
    bits = bits & ~(1 << pos);
}

void BitMask::clear()
{
    bits = 0;
}

