//
//  MBullet.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MBullet.h"
#include "MConsts.h"

USING_NS_CC;

MBullet::MBullet() : _damage(0), _owner(entityTypes::kNone), _speed(0,0) {
};

bool MBullet::init() {
    if (!MGameEntity::init()) {
        return false;
    }
    
    return true;
}

void MBullet::onEnter() {
    Node::onEnter();
    _model = Sprite::create("bullets.png", Rect(5,8,24,32));
    this->addChild(_model);
    scheduleUpdate();
}

void MBullet::reset() {
    _damage = 0;
    _owner = entityTypes::kNone;
    _speed = Vec2(0,0);
}

void MBullet::setSpeed(Vec2 speed) {
    if (this->_speed == speed) {
        return;
    }
    this->_speed = speed;
    float angleRad = speed.getAngle();
    float angleDeg = - CC_RADIANS_TO_DEGREES(angleRad) + 90 ;
    setRotation(angleDeg);
}

bool MLineBullet::init() {
    if(!MBullet::init()){
        return false;
    }
    return true;
}

void MLineBullet::update(float dt) {
    this->setPosition(this->getPosition() + this->_speed * dt);
}

MLineBackBullet::MLineBackBullet() : _distX(0) {};

void MLineBackBullet::setDistX(float distX) {
    _distX = fabsf(distX);
}

bool MLineBackBullet::init() {
    if(!MLineBullet::init()){
        return false;
    }
    return true;
}

void MLineBackBullet::update(float dt) {
    if (_distX > 0) {
        MLineBullet::update(dt);
        _distX -= fabsf(_speed.x * dt);
        if (_distX <= 0) {
            setSpeed(-_speed);
        }
    } else {
        MLineBullet::update(dt);
    }
}

void MLineBackBullet::reset() {
    MLineBullet::reset();
}