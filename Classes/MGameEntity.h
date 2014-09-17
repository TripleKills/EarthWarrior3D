//
//  MGameEntity.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MGameEntity_h
#define EarthWarrior3D_MGameEntity_h

#include "cocos2d.h"
#include "MMacros.h"


class MGameEntity : public cocos2d::Node {
public:
    template <typename T> void initWithJson(const T& document);
    virtual void print();
    
    void forward(float dist);
    void forward(float dist, float angle);

    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE_READONLY(float, _radius, Radius);
    CC_SYNTHESIZE_READONLY(cocos2d::Vec3, _orientation, Orientation);
    CC_SYNTHESIZE(float, _speed, Speed);
protected:
    MGameEntity(){};
    cocos2d::Node* _model;
};

template <typename T> void MGameEntity::initWithJson(const T& document) {
    std::string modelType = document.HasMember("modelType") ? document["modelType"].GetString(): "3d";
    std::string img = document["modelImg"].GetString();
    if (modelType == "3d") {
        std::string obj = document["modelObj"].GetString();
        _model = cocos2d::Sprite3D::create(obj, img);
    } else if (modelType == "2d") {
        if (document.HasMember("modelRect")) {
            cocos2d::Rect rect = MStringUtils::parseRect(document["modelRect"].GetString());
            _model = cocos2d::Sprite::create(img, rect);
        } else {
            _model = cocos2d::Sprite::create(img);
        }
    }
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
        _orientation = cocos2d::Vec3(0,0,0);
    }
    
    _type = entityTypes::kNone;
}

#endif
