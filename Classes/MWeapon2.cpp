//
//  MWeapon2.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-19.
//
//

#include <stdio.h>
#include "MWeapon2.h"
#include "MBullet2.h"

USING_NS_CC;

MWeaponLoader* MWeaponLoader::create() {
    auto loader = new MWeaponLoader();
    loader->autorelease();
    return loader;
}

Vector<MBullet2*> MWeaponLoader::getBullets() {
    Vector<MBullet2*> bullets;
    for (int i = 0 ; i < 8; i++) {
        auto bullet = MBullet2::create();
        auto runner = MBulletRunnerLine::create();
        auto aimer = MBulletAimerStatic::create(2);
        bullet->setAimer(aimer);
        bullet->setRotation(-120);
        bullet->setSpeed(200);
        bullet->setDamage(100);
        bullet->setRunner(runner);
        bullets.pushBack(bullet);
    }
    return bullets;
}

MWeaponEmitterArc* MWeaponEmitterArc::create() {
    auto emitter = new MWeaponEmitterArc();
    emitter->autorelease();
    return emitter;
}

void MWeaponEmitterArc::emmit(cocos2d::Vector<MBullet2*> bullets) {
    auto iter = bullets.begin();
    float time = 0;
    Vec2 vec = Vec2(160, 200);
    float rotation = -50;
    while(iter != bullets.end()) {
        (*iter)->setPosition(vec+=Vec2(5,0));
        (*iter)->getAimer()->setTime(0);
        (*iter)->setRotation(rotation+=10);
        iter++;
    }
}

MWeapon2* MWeapon2::create() {
    auto weapon = new MWeapon2();
    weapon->autorelease();
    return weapon;
}

void MWeapon2::setEmitter(MWeaponEmitter* emitter) {
    this->_emitter = emitter;
    this->_emitter->retain();
}
void MWeapon2::setLoader(MWeaponLoader* loader) {
    this->_loader = loader;
    this->_loader->retain();
}
void MWeapon2::update(float dt) {
    CCASSERT(nullptr != _loader, "must set loader for weapon");
    CCASSERT(nullptr != _emitter, "must set emitter for weapon");
    CCASSERT(nullptr != _bulletsLayer, "must set bullets layer for weapon");
    if (_timePassed < 0 || _timePassed + dt >= _interval) {
        Vector<MBullet2*> bullets = _loader->getBullets();
        _emitter->emmit(bullets);
        auto iter = bullets.begin();
        while(iter != bullets.end()) {
            _bulletsLayer->addChild(*iter);
            iter++;
        }
        if(_timePassed < 0) {
            _timePassed = 0;
        } else {
            _timePassed += dt - _interval;
        }
    } else {
        _timePassed += dt;
    }
}