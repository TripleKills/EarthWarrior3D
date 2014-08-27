//
//  MEnemy.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-19.
//
//

#include "MEnemy.h"
#include "MGeometryUtils.h"

USING_NS_CC;

void MEnemy::onEnter() {
    Node::onEnter();
    scheduleUpdate();
}

void MEnemyLine::print() {
    MAirCraft::print();
}

void MEnemyLine::initWithJson(rapidjson::Document& document) {
    MAirCraft::initWithJson(document);
}

void MEnemyLine::initWithJson(const char* fileName) {
    MAirCraft::initWithJson(fileName);
}

MEnemyLine* MEnemyLine::createWithJson(rapidjson::Document& document){
    auto enemy = new MEnemyLine();
    enemy->initWithJson(document);
    enemy->autorelease();
    return enemy;
}

MEnemyLine* MEnemyLine::createWithJson(const char* fileName) {
    auto enemy = new MEnemyLine();
    enemy->initWithJson(fileName);
    enemy->autorelease();
    return enemy;
}

void MEnemyLine::update(float dt) {
    forward(_speed * dt);
}

MEnemyArc* MEnemyArc::create(float speed, float rotateSpeed) {
    auto enemy = new MEnemyArc();
    enemy->_speed = speed;
    enemy->_rotateSpeed = rotateSpeed;
    enemy->autorelease();
    enemy->_model = Sprite3D::create("playerv002.c3b", "playerv002_256.png");
    enemy->_model->setScale(8);
    enemy->addChild(enemy->_model);
    return enemy;
}

void MEnemyArc::update(float dt) {
    forward(_speed * dt, _rotateSpeed * dt);
}

MEnemyRound* MEnemyRound::create(float radius, float rotateSpeed) {
    auto enemy = new MEnemyRound();
    enemy->_radius = radius;
    enemy->_rotateSpeed = CC_DEGREES_TO_RADIANS(rotateSpeed);
    enemy->autorelease();
    enemy->_model = Sprite3D::create("playerv002.c3b", "playerv002_256.png");
    enemy->_model->setScale(8);
    enemy->addChild(enemy->_model);
    
    return enemy;
}

void MEnemyRound::onEnter() {
    MEnemy::onEnter();
    _center = getPosition() - Vec2(_radius,0);
}

void MEnemyRound::update(float dt) {
    float angle = dt * _rotateSpeed;
    Vec2 curPos = getPosition();
    //Vec2 c = curPos;
    curPos.rotate(_center, angle);
    //CCLOG("center:(%f,%f), cur pos:(%f,%f), new pos(%f,%f)",_center.x, _center.y,c.x,c.y,curPos.x,curPos.y);
    setPosition(curPos);
}

MEnemyStaticAimTarget* MEnemyStaticAimTarget::create(Node* target) {
    auto enemy = new MEnemyStaticAimTarget();
    enemy->_target = target;
    enemy->autorelease();
    enemy->_model = Sprite3D::create("playerv002.c3b", "playerv002_256.png");
    enemy->_model->setScale(8);
    enemy->addChild(enemy->_model);
    return enemy;
}

void MEnemyStaticAimTarget::update(float dt) {
    MGeometryUtils::aim(this, _target);
}