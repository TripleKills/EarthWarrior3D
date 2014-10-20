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
#include "MJsonDataManager.h"
USING_NS_CC;

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

void MBulletAimerStatic::update(float dt) {
    //do nothing
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
    MGeometryUtils::aim(_owner, _target);
}


void MBulletRunnerLine::update(float dt) {
    CCASSERT(_owner != nullptr, "owner must exist");
    _owner->forward(dt * _owner->getSpeed());
}
void MBullet2::initWithJson(Json* document){
    std::string bulletId = Json_getString(document, "bulletId", "");
    Json* bulletJson = Json_getItem(MJsonDataManager::getInstance()->JSON_DOC["bullets"], bulletId.c_str());
    MGameEntity::initWithJson(bulletJson);
    //MGameEntity::initWithJson(document);
    _damage = Json_getInt(document, "damage", 0); //document["damage"].GetInt();
    _owner = entityTypes::kNone;
    
    _runner = nullptr;
    Json* runner = Json_getItem(document, "runner");
    //rapidjson::Value &runner = document["runner"];
    std::string runnerType = Json_getString(runner, "type", "");
    MBulletRunner* mrunner = nullptr;
    if (runnerType == "line") {
        mrunner = MBulletRunnerLine::createWithJson(runner);
    } else if (runnerType == "targeted") {
        mrunner = MBulletRunnerTarget::createWithJson(runner);
    }
    setRunner(mrunner);
    
    _aimer = nullptr;
    Json* aimer = Json_getItem(document, "aimer");
    if (aimer) {
        std::string type = Json_getString(aimer, "type", "");
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

void MBulletAimerStatic::initWithJson(Json* document) {
    float time = Json_getFloat(document, "time", 0.0f);
    CCLOG("MBulletAimerStatic set time to %f", time);
    setTime(time);
    CCLOG("MBulletAimerStatic time is %f", getTime());
}

void MBulletAimerTargeted::initWithJson(Json* document) {
    float time = Json_getFloat(document, "time", 0.0f);
    setTime(time);
    _targetType = Json_getString(document, "target", "");
    _target = nullptr;
}

void MBulletRunnerTarget::initWithJson(Json* document) {
    _targetType = Json_getString(document, "target", "");
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