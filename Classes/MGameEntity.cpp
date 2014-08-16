//
//  MGameEntity.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MGameEntity.h"

USING_NS_CC;

bool MGameEntity::init() {
    if (!Node::init())
        return false;
    return true;
}

void MGameEntity::forward(float dist) {
    float f = getRotation();
    this->setPosition(getPosition()
                +Vec2(
                      sinf(CC_DEGREES_TO_RADIANS(f))*dist,
                      cosf(CC_DEGREES_TO_RADIANS(f))*dist)
                );
}
void MGameEntity::forward(float dist, float angle){
    setRotation(getRotation()-angle);
    forward(dist);
}