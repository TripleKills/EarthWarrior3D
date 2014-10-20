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
/**
template<typename T> void MBullet2::initWithJson(T& document) {
    MGameEntity::initWithJson(document);
    _damage = document["damage"].GetInt();
    _owner = entityTypes::kNone;
    
    _runner = nullptr;
    rapidjson::Value &runner = document["runner"];
    std::string runnerType = runner["type"].GetString();
    MBulletRunner* mrunner = nullptr;
    if (runnerType == "line") {
        mrunner = MBulletRunnerLine::createWithJson(runner);
    } else if (runnerType == "targeted") {
        mrunner = MBulletRunnerTarget::createWithJson(runner);
    }
    setRunner(mrunner);
    
    _aimer = nullptr;
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
*/
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
        _aimer->update(dt);
    } else {
        _runner->update(dt);
    }
}

/**
template<typename T> void MBulletAimerStatic::initWithJson(T& document) {
    float time = document["time"].GetDouble();
    CCLOG("MBulletAimerStatic set time to %f", time);
    setTime(time);
    CCLOG("MBulletAimerStatic time is %f", getTime());
}
 */

void MBulletAimerStatic::update(float dt) {
    //do nothing
}

/**
template<typename T> void MBulletAimerTargeted::initWithJson(T& document) {
    float time = document["time"].GetDouble();
    setTime(time);
    _targetType = document["target"].GetString();
    _target = nullptr;
}
*/
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
    MGeometryUtils::aim(_owner, _target);
}


void MBulletRunnerLine::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    _owner->forward(dt * _owner->getSpeed());
}
void MBullet2::initWithJson(rapidjson::Value& document){
    MGameEntity::initWithJson(document);
    _damage = document["damage"].GetInt();
    _owner = entityTypes::kNone;
    
    _runner = nullptr;
    rapidjson::Value &runner = document["runner"];
    std::string runnerType = runner["type"].GetString();
    MBulletRunner* mrunner = nullptr;
    if (runnerType == "line") {
        mrunner = MBulletRunnerLine::createWithJson(runner);
    } else if (runnerType == "targeted") {
        mrunner = MBulletRunnerTarget::createWithJson(runner);
    }
    setRunner(mrunner);
    
    _aimer = nullptr;
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
};

void MBulletAimerStatic::initWithJson(rapidjson::Value& document) {
    float time = document["time"].GetDouble();
    CCLOG("MBulletAimerStatic set time to %f", time);
    setTime(time);
    CCLOG("MBulletAimerStatic time is %f", getTime());
}

void MBulletAimerTargeted::initWithJson(rapidjson::Value& document) {
    float time = document["time"].GetDouble();
    setTime(time);
    _targetType = document["target"].GetString();
    _target = nullptr;
}

void MBulletRunnerTarget::initWithJson(rapidjson::Value& document) {
    _targetType = document["target"].GetString();
    _target = nullptr;
}
/**
template<typename T> void MBulletRunnerTarget::initWithJson(T& document) {
    _targetType = document["target"].GetString();
    _target = nullptr;
}
*/
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
        auto pos1 = _target->getPosition();
        auto pos2 = _owner->getPosition();
        if (pos1 == pos2) {
            return;
        }
        float dist = pos1.getDistanceSq(pos2);
        if (dist < 5) {
            _owner->setPosition(_target->getPosition());
            return;
        }
    
        MGeometryUtils::aim(_owner, _target);
    }
    _owner->forward(dt * _owner->getSpeed());
}