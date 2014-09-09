//
//  MMacros.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-15.
//
//

#ifndef EarthWarrior3D_MMacros_h
#define EarthWarrior3D_MMacros_h

#include "MJsonUtils.h"
#include "MStringUtils.h"
#include "MGeometryUtils.h"
#include "MConsts.h"
#include "MLayerUtil.h"

#define LOG_FUNC CCLOG("%s\n%s:%d",__FILE__,__FUNCTION__,__LINE__);

#define CREATE_WITH_JSON(__TYPE__) \
protected:\
    __TYPE__(){};\
public:\
    static __TYPE__* createWithJson(const char* fileName) {\
    rapidjson::Document doc;\
    MJsonUtils::loadFileAsJson(fileName, doc);\
    return __TYPE__::createWithJson(doc);\
}\
    template<typename T> static __TYPE__* createWithJson(T& document) {\
    auto enemy = new __TYPE__();\
    enemy->initWithJson(document);\
    enemy->autorelease();\
    return enemy;\
}

#endif
