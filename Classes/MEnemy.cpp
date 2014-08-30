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
using namespace rapidjson;
USING_NS_CC;

void MEnemy::onEnter() {
    Node::onEnter();
    scheduleUpdate();
}



void MEnemy::initWithJson(Document& document) {
    LOG_FUNC
    MAirCraft::initWithJson(document);
}

void MEnemyLine::update(float dt) {
    forward(_speed * dt);
}



void MEnemyArc::initWithJson(rapidjson::Document& document) {
    LOG_FUNC
    MEnemy::initWithJson(document);
    _rotateSpeed = document["rotateSpeed"].GetDouble();
}

void MEnemyArc::print() {
    MAirCraft::print();
    CCLOG("MEnemyArc:[rotate speed:%f]",_rotateSpeed);
}

void MEnemyArc::update(float dt) {
    forward(_speed * dt, _rotateSpeed * dt);
}



void MEnemyRound::print() {
    MAirCraft::print();
    CCLOG("MEnemyRound:[raidus:%f,rotateSpeed:%f]",_radius,_rotateSpeed);
}

void MEnemyRound::initWithJson(rapidjson::Document& document) {
    MEnemy::initWithJson(document);
    _radius = document["radius"].GetDouble();
    _rotateSpeed = CC_DEGREES_TO_RADIANS(document["rotateSpeed"].GetDouble());
}

void MEnemyRound::onEnter() {
    MEnemy::onEnter();
    _center = getPosition() - Vec2(_radius,0);
}

void MEnemyRound::update(float dt) {
    float angle = dt * _rotateSpeed;
    Vec2 curPos = getPosition();
    curPos.rotate(_center, angle);
    setPosition(curPos);
}




void MEnemyStaticAimTarget::initWithJson(Document& document) {
    MEnemy::initWithJson(document);
}

void MEnemyStaticAimTarget::update(float dt) {
    MGeometryUtils::aim(this, _target);
}