//
//  MJsonUtils.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-27.
//
//

#ifndef EarthWarrior3D_MJsonUtils_h
#define EarthWarrior3D_MJsonUtils_h

#include "json/document.h"
#include "cocos2d.h"

class MJsonUtils {
public:
    static bool loadFileAsJson(const char* fileName, rapidjson::Document &jsonDict);
};

#endif
