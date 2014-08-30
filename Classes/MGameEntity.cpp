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

void MGameEntity::initWithJson(const Document& document) {
    std::string obj = document["modelObj"].GetString();
    std::string img = document["modelImg"].GetString();
    _model = Sprite3D::create(obj, img);
    addChild(_model);
    
    if (document.HasMember("speed")) {
        _speed = document["speed"].GetDouble();
    } else {
        _speed = 0.0f;
    }
    
    if(document.HasMember("modelScale")) {
        float scale = document["modelScale"].GetDouble();
        _model->setScale(scale);
    }
    
    if(document.HasMember("rotation")) {
        std::string rotations = document["rotation"].GetString();
        _orientation = MStringUtils::parseVec3(rotations);
        setRotation3D(_orientation);
    } else {
        _orientation = Vec3(0,0,0);
    }
    
    _type = entityTypes::kNone;
}

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