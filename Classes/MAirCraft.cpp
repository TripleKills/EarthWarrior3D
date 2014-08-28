//
//  MAirCraft.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MAirCraft.h"
#include "MJsonUtils.h"
#include <vector>
#include "MStringUtils.h"

USING_NS_CC;
using namespace rapidjson;

bool MAirCraft::init() {
    if (!MGameEntity::init()) {
        return false;
    }
    return true;
}

void MAirCraft::initWithJson(const Document& document) {
    std::string obj = document["modelObj"].GetString();
    std::string img = document["modelImg"].GetString();
    _model = Sprite3D::create(obj, img);
    _speed = document["speed"].GetDouble();
    _hp = document["hp"].GetInt();
    if(document.HasMember("modelScale")) {
        float scale = document["modelScale"].GetDouble();
        _model->setScale(scale);
    }
    if(document.HasMember("rotation")) {
        std::string rotations = document["rotation"].GetString();
        _orientation = MStringUtils::parseVec3(rotations);
        setRotation3D(_orientation);
    }
    addChild(_model);
}

void MAirCraft::initWithJson(const char* fileName) {
    Document doc;
    MJsonUtils::loadFileAsJson(fileName, doc);
    initWithJson(doc);
}

void MAirCraft::print() {
    CCLOG("MAirCraft:[speed:%f, hp:%d, orientation(%f,%f,%f)]", _speed, _hp, _orientation.x, _orientation.y, _orientation.z);
}