//
//  MWeapon.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-17.
//
//

#ifndef EarthWarrior3D_MWeapon_h
#define EarthWarrior3D_MWeapon_h

#include "cocos2d.h"

class MWeapon : public cocos2d::Node {
public:
    virtual void shoot(float dt) = 0;
    virtual void reset() = 0;
};

#endif
