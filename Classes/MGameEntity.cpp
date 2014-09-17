//
//  MGameEntity.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MGameEntity.h"
#include "MStringUtils.h"

USING_NS_CC;
using namespace rapidjson;



void MGameEntity::print() {
    CCLOG("MGameEntity:[speed:%f, orientation(%f,%f,%f), type(%d)]", _speed, _orientation.x, _orientation.y, _orientation.z, _type);
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