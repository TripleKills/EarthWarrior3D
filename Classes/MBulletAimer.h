//
//  MBulletAimer.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-18.
//
//

#ifndef EarthWarrior3D_MBulletAimer_h
#define EarthWarrior3D_MBulletAimer_h

#include "cocos2d.h"
class MBullet2;


class MBulletAimer : public cocos2d::Ref {
public:
    CC_SYNTHESIZE(float, time, Time);
    CC_SYNTHESIZE(MBullet2*, _owner, Owner);
    virtual void update(float dt) = 0;
};

class MBulletAimerStatic : public MBulletAimer {
public:
    static MBulletAimerStatic* create(float time);
    virtual void update(float dt);
};

class MBulletAimerTargeted : public MBulletAimer {
public:
    static MBulletAimerTargeted* create(float time, cocos2d::Node* target);
    virtual void update(float dt);
private:
    cocos2d::Node* _target;
};

#endif
