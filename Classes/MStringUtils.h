//
//  MStringUtils.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MStringUtils_h
#define EarthWarrior3D_MStringUtils_h

#include "cocos2d.h"

class MStringUtils {
public:
    static std::string removeDirAndReplacePostfix(const char* plist, const char* newPostfix);
};

#endif
