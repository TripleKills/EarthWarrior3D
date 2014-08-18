//
//  MBulletRunner.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-18.
//
//

#ifndef EarthWarrior3D_MBulletRunner_h
#define EarthWarrior3D_MBulletRunner_h

#include "cocos2d.h"

class MBullet2;

class MBulletRunner : public cocos2d::Ref {
public:
    virtual void update(float dt) = 0;
    CC_SYNTHESIZE(MBullet2*, _owner, Owner);
};

class MBulletRunnerLine : public MBulletRunner {
public:
    static MBulletRunnerLine* create();
    virtual void update(float dt);
};

#endif
