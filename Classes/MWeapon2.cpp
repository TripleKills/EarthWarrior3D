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
#include "MJsonDataManager.h"
#include "MGameScene.h"
USING_NS_CC;

Vector<MBullet2*> MWeaponLoader::getBullets() {
    Vector<MBullet2*> bullets;
    for (int i = 0 ; i < _bulletNum; i++) {
        auto bullet = MBullet2::createWithJson(doc);
        bullets.pushBack(bullet);
        bullet->setFace(_owner->getFace());
    }
    return bullets;
}

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
        (*iter)->rotate(startRotation);
        iter++;
        startRotation+=deltaRotation;
        start += deltaWidth;
    }
}

void MWeaponEmitterParallel::emmit(cocos2d::Vector<MBullet2*> bullets) {
    auto iter = bullets.begin();
    int count = bullets.size();
    float width = 50;
    Vec2 start = Vec2(- width / 2, 20);
    Vec2 deltaWidth = Vec2(width/count,0);
    while(iter != bullets.end()) {
        (*iter)->setPosition(start);
        start += deltaWidth;
        iter++;
    }
}

void MWeapon2::setEmitter(MWeaponEmitter* emitter) {
    this->_emitter = emitter;
    this->_emitter->setOwner(this);
    this->_emitter->retain();
}
void MWeapon2::setLoader(MWeaponLoader* loader) {
    this->_loader = loader;
    this->_loader->setOwner(this);
    this->_loader->retain();
}
void MWeapon2::onEnter() {
    Node::onEnter();
    if (_bulletsLayer == nullptr) {
        auto gameScene = Director::getInstance()->getRunningScene();
        Vector<Node*> children = gameScene->getChildren();
        Node* bulletLayer = children.at(0)->getChildByTag(SceneZOrder::game_layer)->getChildByTag(GameZOrder::bullet_layer);
        this->setBulletsLayer(bulletLayer);
    }
    if (getParentWeapon() == nullptr) {
        scheduleUpdate();
    }
}

void MWeapon2::addChildWeapon(MWeapon2* child) {
    _weapons.pushBack(child);
    addChildEntity(child);
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
    if (_weapons.empty()) {
        CCASSERT(nullptr != _loader, "must set loader for weapon");
        CCASSERT(nullptr != _emitter, "must set emitter for weapon");
        CCASSERT(nullptr != _bulletsLayer, "must set bullets layer for weapon");
    }
    
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
void MWeapon2::initWithJson(Json* document) {
    this->_bulletsLayer = nullptr;
    this->_loader = nullptr;
    this->_emitter = nullptr;
    this->_groupTimePassed = 0.0f;
    this->_parent = nullptr;
    this->_interval = 0.0f;
    this->_groupFireTime = 0.0f;
    Json* weaponsValue = Json_getItem(document, "weapons");
    if (weaponsValue) {
        Json* child = weaponsValue->child;
        while(child) {
            auto weapon = MWeapon2::createWithJson(child);
            addChildWeapon(weapon);
            child = child->next;
        }
        return;
    }
    
    
    this->_interval = Json_getFloat(document, "fireInterval", 0.0f);
    this->_groupFireTime = Json_getFloat(document, "groupFireTime", 0.0f);
    
    std::string loaderId = Json_getString(document, "loaderId", "");
    Json* loaderValue = Json_getItem(MJsonDataManager::getInstance()->JSON_DOC["weaponLoaders"], loaderId.c_str());
    auto loader = MWeaponLoader::createWithJson(loaderValue);
    setLoader(loader);
    
    Json* emitterValue = Json_getItem(document,"emitter");
    std::string emitterType = Json_getString(emitterValue, "type", "");
    if (emitterType == "arc") {
        setEmitter(MWeaponEmitterArc::createWithJson(emitterValue));
    } else if (emitterType == "parallel") {
        setEmitter(MWeaponEmitterParallel::createWithJson(emitterValue));
    }
}

void MWeaponLoader::initWithJson(Json* document) {
    _owner = nullptr;
    this->_bulletNum = Json_getInt(document, "num", 1);
    
    doc = Json_getItem(document, "bullet");
}