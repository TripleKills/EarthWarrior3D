//
//  MEnemyGeneral.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-21.
//
//

#include "MEnemyGeneral.h"
#include "MJsonDataManager.h"
#include "MGameScene.h"
USING_NS_CC;

MEnemyGeneral* MEnemyGeneral::_sInstance = nullptr;

MEnemyGeneral::MEnemyGeneral() : _timePassed(0.0f), _interval(0.5f),
                                _timeInterval(0.0f), _mMajors(){
                                    init();
}

void MEnemyGeneral::init() {
}

MEnemyGeneral::~MEnemyGeneral() {
    _mMajors.clear();
}

void MEnemyGeneral::destroy() {
    if (nullptr != _sInstance) {
        CC_SAFE_DELETE(_sInstance);
    }
}

void MEnemyGeneral::update(float dt) {
    _timePassed += dt;
    if (_timeInterval == 0 or _timeInterval + dt >= _interval) {
        auto major = _mMajors.back();
        float subDt = _timeInterval == 0 ? dt : _timeInterval + dt;
        if (!major->update(subDt)) {
            _mMajors.popBack();
        }
    }
    _timeInterval += dt;
    _timeInterval = _timeInterval >= _interval ? _timeInterval - _interval : _timeInterval;
}

MEnemyMajor::MEnemyMajor() : _time(-1), _colonels(), _timePassed(0.0f) {
    
}

bool MEnemyMajor::init() {
    return true;
}

bool MEnemyMajor::update(float dt) {
    _timePassed += dt;
    
    if (_time != MEnemyMajor::K_LOOP_INTERVAL && _timePassed >= _time) {
        bool ret = false;
        for(int i = _colonels.size()-1; i >= 0; i-- ) {
            auto colonel = _colonels.at(i);
            if (colonel->flee(dt)) {
                ret = true;
            } else {
                _colonels.erase(i);
            }
        }
        return ret;
    }
    
    
    bool result = false;
    for(int i = _colonels.size()-1; i >= 0; i-- ) {
        auto colonel = _colonels.at(i);
        bool ret = colonel->update(dt);
        
        bool isLoop = colonel->isLoop();
        if (!ret && !isLoop) {
            _colonels.erase(i);
        } else if (ret) {
            result = true;
        }
    }
    return result;
}

void MEnemyMajor::activate() {
}


void MEnemyColonel::initWithJson(Json* document) {
    _timePassed = 0.0f;
    _interval = Json_getFloat(document, "interval", -1.0f);
    _fleeSpeed = Json_getFloat(document, "fleeSpeed", 500);
    Json* deployJson = Json_getItem(document, "deployer");
    _deployer = MEnemyColonelDeployer::createWithJson(deployJson);
    Json* conscripterJson =Json_getItem(document, "conscripter");
    _conscripter = MEnemyColonelConscripter::createWithJson(conscripterJson);
}
MEnemyColonel::~MEnemyColonel() {
    
}

bool MEnemyColonel::init() {
    return true;
}

bool MEnemyColonel::flee(float dt) {
    for (auto iter = _mSoldiers.begin(); iter != _mSoldiers.end(); iter++) {
        (*iter)->unscheduleUpdate();
        float dist = (*iter)->getPosition().getDistance((*iter)->getPosition() + Vec2(0, _fleeSpeed*dt));
        (*iter)->forward(dist);
    }
    return !_mSoldiers.empty();
}

void MEnemyColonel::activate() {
}

bool MEnemyColonel::isLoop() {
    return _interval != MEnemyColonel::K_ONCE_INTERVAL;
}

void MEnemyColonel::launchAForce() {
    _conscripter->conscript(_mSoldiers);
    _deployer->deployEnemys(_mSoldiers);
}

bool MEnemyColonel::update(float dt) {
    if (_timePassed == 0) {
        launchAForce();
    } else if (_timePassed + dt >= _interval && _interval != MEnemyColonel::K_ONCE_INTERVAL
               && _mSoldiers.empty()) {
        launchAForce();
    }
    
    _timePassed += dt;
    if (_interval != MEnemyColonel::K_ONCE_INTERVAL) {
        _timePassed = _timePassed < _interval ? _timePassed : _timePassed - _interval;
    }
    
    return !_mSoldiers.empty();
}


bool MEnemyColonelConscripter::init() {
    return true;
}

void MEnemyColonelConscripter::conscript(cocos2d::Vector<MEnemy*>& enemies) {
    enemies.clear();
    Json* child = _enemyJson->child;
    while (child) {
        std::string enemyName = child->valueString;
        Json* enemyJson = Json_getItem(MJsonDataManager::getInstance()->JSON_DOC["enemies"],enemyName.c_str());
        auto enemy = MEnemyLine::createWithJson(enemyJson);
        enemies.pushBack(enemy);
        child = child->next;
    }
}

void MEnemyColonelConscripter::initWithJson(Json* document) {
    _enemyJson = document;
}

bool MEnemyColonelDeployer::init() {
    return true;
}

void MEnemyColonelDeployer::deployEnemys(Vector<MEnemy*>& enemys) {
    
    auto gameScene = Director::getInstance()->getRunningScene();
    Vector<Node*> children = gameScene->getChildren();
    Node* enemylayer = children.at(0)->getChildByTag(SceneZOrder::game_layer)->getChildByTag(GameZOrder::enemy_layer);
    
    std::vector<cocos2d::Vec2> _mpositions;
    Json* child = _posJson->child;
    while (child) {
        _mpositions.push_back(MStringUtils::parseVec2(child->valueString));
        child = child->next;
    }

    for (int i = 0; i < enemys.size(); i++) {
        MEnemy* enemy = enemys.at(i);
        int size = _mpositions.size();
        int posIndex = i >= size ? size - 1 : i;
        enemy->setPosition(_mpositions.at(posIndex));
        enemylayer->addChild(enemy);
    }
}

void MEnemyColonelDeployer::initWithJson(Json* document) {
    _posJson = document;
}