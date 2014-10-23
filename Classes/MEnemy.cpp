//
//  MEnemy.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-19.
//
//

#include "MEnemy.h"
#include "MGeometryUtils.h"

#include "MMacros.h"
#include "MWeapon2.h"
#include "MJsonDataManager.h"
#include "MGameScene.h"

USING_NS_CC;

void MEnemy::onEnter() {
    Node::onEnter();
    scheduleUpdate();
}



void MEnemy::initWithJson(Json* document) {
    LOG_FUNC
    MAirCraft::initWithJson(document);
    Json* weaponDef = Json_getItem(document, "weapon");
    std::string weaponId = Json_getString(weaponDef, "weaponId", "");
    Json* realWeapon = Json_getItem(MJsonDataManager::getInstance()->JSON_DOC["weapons"], weaponId.c_str());
    _weapon = MWeapon2::createWithJson(realWeapon);
    this->addChildEntity(_weapon);
    _weapon->setPosition(MStringUtils::parseVec2(Json_getString(weaponDef, "position", "0,0")));
}

void MEnemy::update(float dt) {
    _weapon->update(dt);
    checkScreenState(dt);
}

void MEnemyLine::update(float dt) {
    MEnemy::update(dt);
    forward(_speed * dt);
}



void MEnemyArc::initWithJson(Json* document) {
    LOG_FUNC
    MEnemy::initWithJson(document);
    _rotateSpeed = Json_getFloat(document, "rotateSpeed", 0.0f);
    //_rotateSpeed = document["rotateSpeed"].GetDouble();
}

void MEnemyArc::print() {
    MAirCraft::print();
    CCLOG("MEnemyArc:[rotate speed:%f]",_rotateSpeed);
}

void MEnemyArc::update(float dt) {
    MEnemy::update(dt);
    forward(_speed * dt, _rotateSpeed * dt);
}



void MEnemyRound::print() {
    MAirCraft::print();
    CCLOG("MEnemyRound:[raidus:%f,rotateSpeed:%f]",_radius,_rotateSpeed);
}

void MEnemyRound::initWithJson(Json* document) {
    LOG_FUNC
    MEnemy::initWithJson(document);
    _radius = Json_getFloat(document, "radius", 0.0f);
    _rotateSpeed = CC_DEGREES_TO_RADIANS(Json_getFloat(document, "rotateSpeed", 0.0f));
}

void MEnemyRound::onEnter() {
    MEnemy::onEnter();
    _center = getPosition() - Vec2(_radius,0);
}

void MEnemyRound::update(float dt) {
    MEnemy::update(dt);
    float angle = dt * _rotateSpeed;
    Vec2 curPos = getPosition();
    curPos.rotate(_center, angle);
    setPosition(curPos);
}




void MEnemyStaticAimTarget::initWithJson(Json* document) {
    MEnemy::initWithJson(document);
}

void MEnemyStaticAimTarget::update(float dt) {
    MGeometryUtils::aim(this, _target);
}