//
//  CCollider.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/9/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "CCollider.hpp"

CCollider::CCollider(Object* owner)
:Component(owner), layer(CollisionLayer::Default){}

CCollider::~CCollider(){}

CollisionLayer CCollider::getLayer() const
{
    return layer;
}

void CCollider::setLayer(CollisionLayer layer)
{
    this->layer = layer;
}
