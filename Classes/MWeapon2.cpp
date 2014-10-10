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

Vector<MBullet2*> MWeaponLoader::getBullets() {
    Vector<MBullet2*> bullets;
    //rapidjson::Value& bulletDef = doc["bullet"];
   // bulletDef["speed"].GetInt();
    for (int i = 0 ; i < _bulletNum; i++) {
        auto bullet = MBullet2::createWithJson(doc);
    //    bullet->setRotation(-120);
        bullets.pushBack(bullet);
    }
    return bullets;
}

/**
MWeaponEmitterArc* MWeaponEmitterArc::create() {
    auto emitter = new MWeaponEmitterArc();
    emitter->autorelease();
    return emitter;
}
*/
void MWeaponEmitterArc::emmit(cocos2d::Vector<MBullet2*> bullets) {
    auto iter = bullets.begin();
    int count = bullets.size();
    float totalRotation = 50;
    float width = 50;
    Vec2 start = Vec2(- width / 2, 20);
    Vec2 deltaWidth = Vec2(width/count,0);
    
    float time = 3;
    float startRotation = - totalRotation / 2;
    float deltaRotation = totalRotation / count;
    while(iter != bullets.end()) {
        (*iter)->setPosition(start);
        //(*iter)->getAimer()->setTime(3);
        (*iter)->setRotation(startRotation);
        iter++;
        startRotation+=deltaRotation;
        start += deltaWidth;
    }
}

/**
MWeaponEmitterParallel* MWeaponEmitterParallel::create() {
    auto emitter = new MWeaponEmitterParallel();
    emitter->autorelease();
    return emitter;
}
*/
void MWeaponEmitterParallel::emmit(cocos2d::Vector<MBullet2*> bullets) {
    auto iter = bullets.begin();
    int count = bullets.size();
    float width = 50;
    Vec2 start = Vec2(- width / 2, 20);
    Vec2 deltaWidth = Vec2(width/count,0);
    while(iter != bullets.end()) {
        (*iter)->setPosition(start);
        start += deltaWidth;
        //(*iter)->getAimer()->setTime(3);
    //    (*iter)->setRotation(rotation+=10);
        iter++;
    }
}
/**
MWeapon2* MWeapon2::create() {
    auto weapon = new MWeapon2();
    weapon->autorelease();
    return weapon;
}
*/
void MWeapon2::setEmitter(MWeaponEmitter* emitter) {
    this->_emitter = emitter;
    this->_emitter->retain();
}
void MWeapon2::setLoader(MWeaponLoader* loader) {
    this->_loader = loader;
    this->_loader->retain();
}
void MWeapon2::onEnter() {
    Node::onEnter();
    if (getParentWeapon() == nullptr) {
        scheduleUpdate();
    }
}

void MWeapon2::addChildWeapon(MWeapon2* child) {
    _weapons.pushBack(child);
    addChild(child);
    child->setParentWeapon(this);
}

void MWeapon2::setBulletsLayer(Node* layer) {
    if (_weapons.empty()) {
        this->_bulletsLayer = layer;
    } else {
        auto iter = _weapons.begin();
        while(iter != _weapons.end()) {
            (*iter++)->setBulletsLayer(layer);
        }
    }
}

void MWeapon2::update(float dt) {
    CCASSERT(nullptr != _loader, "must set loader for weapon");
    CCASSERT(nullptr != _emitter, "must set emitter for weapon");
    CCASSERT(nullptr != _bulletsLayer, "must set bullets layer for weapon");
    if (_timePassed < 0 || _timePassed + dt >= _interval) {
        if (_weapons.empty()) {
            Vector<MBullet2*> bullets = _loader->getBullets();
            _emitter->emmit(bullets);
            auto iter = bullets.begin();
            while(iter != bullets.end()) {
                _bulletsLayer->addChild(*iter);
                Vec2 pos = convertToWorldSpace((*iter)->getPosition());
                (*iter)->setPosition(_bulletsLayer->convertToNodeSpace(pos));
                iter++;
            }
        } else {
            if (!_weapons.at(_weapons.size() - 1)->canFireInGroup()) {
                auto iter = _weapons.begin();
                while(iter != _weapons.end()) {
                    (*iter++)->enableGroupFire();
                }
                _weapons.at(0)->update(dt);
            } else {
                auto iter = _weapons.begin();
                while(iter != _weapons.end()) {
                    if ((*iter)->canFireInGroup()) {
                        (*iter)->update(dt);
                        break;
                    }
                    iter++;
                }
            }
        }
        if(_timePassed < 0) {
            _timePassed = 0;
        } else {
            _timePassed += dt - _interval;
        }
    } else {
        _timePassed += dt;
    }
    _groupTimePassed += dt;
}