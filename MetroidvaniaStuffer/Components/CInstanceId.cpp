//
//  CInstanceId.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/14/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "CInstanceId.hpp"

int CInstanceId::count = 0;

CInstanceId::CInstanceId(Object* owner) : Component(owner), id(count++){}

CInstanceId::~CInstanceId(){}

int CInstanceId::get() const
{
    return id;
}
