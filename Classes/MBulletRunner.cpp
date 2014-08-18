//
//  MBulletRunner.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-18.
//
//

#include "MBulletRunner.h"
#include "MBullet2.h"

MBulletRunnerLine* MBulletRunnerLine::create() {
    auto runner = new MBulletRunnerLine();
    runner->autorelease();
    return runner;
}

void MBulletRunnerLine::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    _owner->forward(dt * _owner->getSpeed());
}