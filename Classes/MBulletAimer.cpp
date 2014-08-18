//
//  MBulletAimer.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-18.
//
//

#include "MBulletAimer.h"
#include "MBullet2.h"

USING_NS_CC;

MBulletAimerStatic* MBulletAimerStatic::create(float time) {
    auto aimer = new MBulletAimerStatic();
    aimer->autorelease();
    aimer->setTime(time);
    return aimer;
}

void MBulletAimerStatic::update(float dt) {
    //do nothing
}

MBulletAimerTargeted* MBulletAimerTargeted::create(float time, Node* target) {
    auto aimer = new MBulletAimerTargeted();
    aimer->autorelease();
    aimer->setTime(time);
    aimer->_target = target;
    return aimer;
}

void MBulletAimerTargeted::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    CCASSERT(_target != nullptr, "_target must exist");
    Vec2 delta = _target->getPosition() - _owner->getPosition();
    float angleRad = delta.getAngle();
    float angleDeg = CC_RADIANS_TO_DEGREES(angleRad);
    if (_owner->getRotation() != 90 - angleDeg) {
        _owner->setRotation(90 - angleDeg);
    }
}