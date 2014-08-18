//
//  MBullet2.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-18.
//
//

#include "MBullet2.h"

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

void MBullet2::update(float dt) {
    CCASSERT(_runner != nullptr, "must set runner");
    _timePassed += dt;
    if(nullptr != _aimer && _timePassed <= _aimer->getTime()) {
        _aimer->update(dt);
    } else {
        _runner->update(dt);
    }
}