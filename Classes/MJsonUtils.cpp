//
//  MJsonUtils.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-27.
//
//

#include "MJsonUtils.h"

USING_NS_CC;

Json* MJsonUtils::loadFileAsJson(const char* fileName){
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(fileName);
    Json* json = Json_create(contentStr.c_str());
    return json;
}