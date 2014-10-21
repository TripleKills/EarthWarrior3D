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

void MGameEntity::initWithJson(Json* document) {
    
    std::string modelType = Json_getString(document, "modelType", "3d");
    std::string img = Json_getString(document, "modelImg", "");
    if (modelType == "3d") {
        std::string obj = Json_getString(document, "modelObj", "");
        _model = cocos2d::Sprite3D::create(obj, img);
    } else if (modelType == "2d") {
        const char* modelRect = Json_getString(document, "modelRect", nullptr);
        if (modelRect) {
            cocos2d::Rect rect = MStringUtils::parseRect(modelRect);
            _model = cocos2d::Sprite::create(img, rect);
        } else {
            _model = cocos2d::Sprite::create(img);
        }
    }
    addChild(_model);
    
    _speed = Json_getInt(document, "speed", 0);
    
    _model->setScale(Json_getFloat(document, "modelScale", 1.0f));
    
    const char* rotations = Json_getString(document, "rotation", nullptr);
    if(rotations) {
        _orientation = MStringUtils::parseVec3(rotations);
        setRotation3D(_orientation);
    } else {
        _orientation = cocos2d::Vec3(0,0,0);
    }
    std::string face = Json_getString(document, "face", "down");
    _face = face == "down" ? DOWN : UP;
    _type = entityTypes::kNone;
}

void MGameEntity::print() {
    CCLOG("MGameEntity:[speed:%f, orientation(%f,%f,%f), type(%d)]", _speed, _orientation.x, _orientation.y, _orientation.z, _type);
}

void MGameEntity::addChildEntity(MGameEntity* child) {
    addChild(child);
    child->setFace(_face);
}

void MGameEntity::forward(float dist) {
    float f = getRotation();
    int faceK = _face == DOWN ? -1 : 1;
    this->setPosition(getPosition()
                +Vec2(
                      sinf(CC_DEGREES_TO_RADIANS(f))*dist*faceK,
                      cosf(CC_DEGREES_TO_RADIANS(f))*dist*faceK)
                );
}

void MGameEntity::forward(float dist, float angle){
    setRotation(getRotation()-angle);
    forward(dist);
}

void MGameEntity::rotate(float angle) {
    int faceK = _face == DOWN ? -1 : 1;
    setRotation(faceK * angle);
}

void MGameEntity::setFace(EntityFaces face) {
    _face = face;
    auto children = getChildren();
    for(auto iter = children.begin(); iter != children.end(); iter++) {
        MGameEntity* entity = dynamic_cast<MGameEntity*>(*iter);
        if (entity != nullptr) {
            entity->setFace(face);
        }
    }
}
