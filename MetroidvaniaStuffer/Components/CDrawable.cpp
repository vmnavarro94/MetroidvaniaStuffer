//
//  CDrawable.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/8/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "CDrawable.hpp"

CDrawable::CDrawable()
:sortOrder(0) {}

CDrawable::~CDrawable() {}

void CDrawable::setSortOrder(int order)
{
    sortOrder = order;
}

int CDrawable::getSortOrder()
{
    return sortOrder;
}
