//
//  MJsonUtils.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-27.
//
//

#ifndef EarthWarrior3D_MJsonUtils_h
#define EarthWarrior3D_MJsonUtils_h

#include "cocos2d.h"
#include "spine/Json.h"

class MJsonUtils {
public:
    static Json* loadFileAsJson(const char* fileName);
};

#endif
