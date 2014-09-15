//
//  MBullet2.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-18.
//
//

#include "MBullet2.h"
#include "MGeometryUtils.h"
#include "MGameController.h"
#include "MMacros.h"

USING_NS_CC;
using namespace rapidjson;

void MBullet2::initWithJson(Document& document) {
    MGameEntity::initWithJson(document);
    _damage = document["damage"].GetInt();
    _owner = entityTypes::kNone;
    
    rapidjson::Value &runner = document["runner"];
    auto mrunner = MBulletRunnerLine::createWithJson(runner);
    setRunner(mrunner);
    
    if (document.HasMember("aimer")) {
        rapidjson::Value &aimer = document["aimer"];
        std::string type = aimer["type"].GetString();
        MBulletAimer* maimer = nullptr;
        if (type == "static") {
            maimer = MBulletAimerStatic::createWithJson(aimer);
        } else if (type == "targeted") {
            maimer = MBulletAimerTargeted::createWithJson(aimer);
        }
        setAimer(maimer);
    }
    
    
    _timePassed = 0;
}

void MBullet2::print() {
    MGameEntity::print();
    CCLOG("MBullet2:[damage:%d, owner:%d]", _damage, _owner);
}

void MBullet2::onEnter() {
    Node::onEnter();
    this->scheduleUpdate();
}

void MBullet2::reset() {
    _timePassed = 0;
}

void MBullet2::setAimer(MBulletAimer* aimer) {
    LOG_FUNC
    this->_aimer = aimer;
    this->_aimer->retain();
    this->_aimer->setOwner(this);
};
void MBullet2::setRunner(MBulletRunner* runner) {
    LOG_FUNC
    this->_runner = runner;
    this->_runner->retain();
    this->_runner->setOwner(this);
};

void MBullet2::update(float dt) {
    CCASSERT(_runner != nullptr, "must set runner");
    _timePassed += dt;
    if(nullptr != _aimer && _timePassed <= _aimer->getTime()) {
        CCLOG("AIMER UPDATE");
        _aimer->update(dt);
    } else {
        CCLOG("runner update");
        _runner->update(dt);
    }
}


template<typename T> void MBulletAimerStatic::initWithJson(T& document) {
    float time = document["time"].GetDouble();
    CCLOG("MBulletAimerStatic set time to %f", time);
    setTime(time);
    CCLOG("MBulletAimerStatic time is %f", getTime());
}

void MBulletAimerStatic::update(float dt) {
    //do nothing
}


template<typename T> void MBulletAimerTargeted::initWithJson(T& document) {
    float time = document["time"].GetDouble();
    setTime(time);
    _targetType = document["target"].GetString();
}

void MBulletAimerTargeted::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    if (nullptr == _target) {
        if (_targetType == "player") {
            _target = MGameController::getInstance()->getPlayer();
        } else if (_targetType == "enemy") {
            _target = MGameController::getInstance()->getRandomEnemy();
        }
    }
    if (nullptr == _target) {
        return;
    }
    CCLOG("owner reference %d", _owner->getReferenceCount());
    CCLOG("target reference %d", _target->getReferenceCount());
    MGeometryUtils::aim(_owner, _target);
}


void MBulletRunnerLine::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    _owner->forward(dt * _owner->getSpeed());
}

template<typename T> void MBulletRunnerTarget::initWithJson(T& document) {
    _targetType = document["target"].GetString();
}

void MBulletRunnerTarget::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    if (nullptr == _target) {
        if (_targetType == "player") {
            _target = MGameController::getInstance()->getPlayer();
        } else if (_targetType == "enemy") {
            _target = MGameController::getInstance()->getRandomEnemy();
        }
    }
    if (nullptr != _target) {
        MGeometryUtils::aim(_owner, _target);
    }
    _owner->forward(dt * _owner->getSpeed());
}