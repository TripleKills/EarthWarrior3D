//
//  MLayerUtil.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MLayerUtil_h
#define EarthWarrior3D_MLayerUtil_h

#include "cocos2d.h"

class MLayerUtil {
public:
    static void addLayerSameZorderTag(cocos2d::Node* node, int zorder);
    static void addLayerSameZorderTag(int first, int last, cocos2d::Node* node);
};

#endif
