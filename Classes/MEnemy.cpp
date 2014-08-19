//
//  MEnemy.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-19.
//
//

#include "MEnemy.h"


USING_NS_CC;

void MEnemy::onEnter() {
    Node::onEnter();
    scheduleUpdate();
}

MEnemyLine* MEnemyLine::create(float speed) {
    auto enemy = new MEnemyLine();
    enemy->_speed = speed;
    enemy->autorelease();
    enemy->_model = Sprite3D::create("playerv002.c3b", "playerv002_256.png");
    enemy->_model->setScale(8);
    enemy->addChild(enemy->_model);
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