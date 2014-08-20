//
//  MBullet2.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-18.
//
//

#include "MBullet2.h"
#include "MGeometryUtils.h"

USING_NS_CC;

bool MBullet2::init() {
    if(!Node::init()){
        return false;
    }
    return true;
}
void MBullet2::onEnter() {
    Node::onEnter();
    _model = Sprite::create("bullets.png", Rect(5,8,24,32));
    this->addChild(_model);
    this->scheduleUpdate();
}

void MBullet2::reset() {
    _timePassed = 0;
}

void MBullet2::setAimer(MBulletAimer* aimer) {
    this->_aimer = aimer;
    this->_aimer->retain();
    this->_aimer->setOwner(this);
};
void MBullet2::setRunner(MBulletRunner* runner) {
    this->_runner = runner;
    this->_runner->retain();
    this->_runner->setOwner(this);
};

void MBullet2::update(float dt) {
    CCASSERT(_runner != nullptr, "must set runner");
    _timePassed += dt;
    if(nullptr != _aimer && _timePassed <= _aimer->getTime()) {
        _aimer->update(dt);
    } else {
        _runner->update(dt);
    }
}

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
    MGeometryUtils::aim(_owner, _target);
}

MBulletRunnerLine* MBulletRunnerLine::create() {
    auto runner = new MBulletRunnerLine();
    runner->autorelease();
    return runner;
}

void MBulletRunnerLine::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    _owner->forward(dt * _owner->getSpeed());
}

MBulletRunnerTarget* MBulletRunnerTarget::create() {
    auto runner = new MBulletRunnerTarget();
    runner->autorelease();
    return runner;
}

void MBulletRunnerTarget::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    CCASSERT(_target != nullptr, "target must exist");
    MGeometryUtils::aim(_owner, _target);
    _owner->forward(dt * _owner->getSpeed());
}