//
//  MJsonUtils.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-27.
//
//

#include "MJsonUtils.h"

using namespace rapidjson;
USING_NS_CC;

bool MJsonUtils::loadFileAsJson(const char* fileName, rapidjson::Document &jsonDict){
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(fileName);
    jsonDict.Parse<0>(contentStr.c_str());
    return jsonDict.HasParseError();
}