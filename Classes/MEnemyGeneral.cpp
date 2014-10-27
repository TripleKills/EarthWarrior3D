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
#include "MEventData.h"
USING_NS_CC;

MEnemyGeneral* MEnemyGeneral::_sInstance = nullptr;

MEnemyGeneral::MEnemyGeneral() : _timePassed(0.0f), _mMajors(){
                                    
}

void MEnemyGeneral::initWithJson(Json* document) {
    Json* majorsJson = Json_getItem(document, "majors");
    Json* child = majorsJson->child;
    while (child) {
        const char* majorName = child->valueString;
        Json* majorJson = Json_getItem(MJsonDataManager::getInstance()->JSON_DOC["majors"], majorName);
        MEnemyMajor* major = MEnemyMajor::createWithJson(majorJson);
        _mMajors.pushBack(major);
        child = child->next;
    }
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
    auto major = _mMajors.back();
    if (!major->update(dt)) {
        _mMajors.popBack();
    }
}





void MEnemyMajor::initWithJson(Json* document) {
    _time = Json_getFloat(document, "fightTime", K_LOOP_INTERVAL);
    Json* colonelsJson = Json_getItem(document, "colonels");
    Json* child = colonelsJson->child;
    while (child) {
        const char* colonelName = Json_getString(child, "name", "");
        float delay = Json_getFloat(child, "delay", -1);
        Json* colonelJson = Json_getItem(MJsonDataManager::getInstance()->JSON_DOC["colonels"], colonelName);
        MEnemyColonel* colonel = MEnemyColonel::createWithJson(colonelJson);
        if (delay > 0) {
            colonel->setFirstDelay(delay);
        }
        _colonels.pushBack(colonel);
        child = child->next;
    }
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
    _deployer->retain();
    Json* conscripterJson =Json_getItem(document, "conscripter");
    _conscripter = MEnemyColonelConscripter::createWithJson(conscripterJson);
    _conscripter->retain();
}
MEnemyColonel::~MEnemyColonel() {
    unregisterEvents();
    CC_SAFE_RELEASE_NULL(_deployer);
    CC_SAFE_RELEASE_NULL(_conscripter);
}

MEnemyColonel::MEnemyColonel() : _interval(0), _timePassed(0), _fleeSpeed(0),
_delayTimePassed(0),_conscripter(nullptr),
_deployer(nullptr), _mSoldiers() {
    registerEvents();
}

void MEnemyColonel::checkSolderFleeOrDead(cocos2d::EventCustom* event) {
    MEventData* data = static_cast<MEventData*>(event->getUserData());
    MEnemy* enemy = dynamic_cast<MEnemy*>(data->obj);
    if (nullptr == enemy) {
        return;
    }
    if (_mSoldiers.contains(enemy)) {
        _mSoldiers.eraseObject(enemy);
        CCLOG("erase enemy when %s", event->getEventName().c_str());
    }
}

void MEnemyColonel::registerEvents() {
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    EventListenerCustom* entityGoOutScreen = EventListenerCustom::create("entity_go_out",
                                                                         CC_CALLBACK_1( MEnemyColonel::checkSolderFleeOrDead, this));
    dispatcher->addEventListenerWithFixedPriority(entityGoOutScreen, 1);
}

void MEnemyColonel::unregisterEvents() {
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeCustomEventListeners("entity_go_out");
}

bool MEnemyColonel::flee(float dt) {
    for (auto iter = _mSoldiers.begin(); iter != _mSoldiers.end(); iter++) {
     //   (*iter)->unscheduleUpdate();
        (*iter)->setFlee(true);
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
    if ( (_delayTimePassed += dt) < 0 ) {
        return true;
    }
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