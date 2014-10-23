//
//  MEventData.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-10-23.
//
//

#ifndef EarthWarrior3D_MEventData_h
#define EarthWarrior3D_MEventData_h

#include "cocos2d.h"

class MEventData {
public:
    MEventData(cocos2d::Ref* obj, cocos2d::ValueMap* map = nullptr) :
                obj(obj), map(map){
                    CC_SAFE_RETAIN(obj);};
    ~MEventData() {
        CC_SAFE_DELETE(map);
        CC_SAFE_RELEASE_NULL(obj);
    };
    cocos2d::ValueMap* map;
    cocos2d::Ref* obj;
};

#endif