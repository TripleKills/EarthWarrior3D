//
//  MPlayer.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MPlayer.h"

USING_NS_CC;

bool MPlayer::init() {
    if (!MAirCraft::init()) {
        return false;
    }
    return true;
}

void MPlayer::onEnter() {
    Node::onEnter();
    _model = Sprite3D::create("playerv002.c3b", "playerv002_256.png");
    _model->setScale(8);
    this->addChild(_model);
    
    initTouchEvent();
}

void MPlayer::initTouchEvent() {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto vecLeftBottom = Vec2(60, 30);
    auto vecRightTop = Vec2(visibleSize.width - 60, visibleSize.height - 55);
    auto onTouchMoved = [vecLeftBottom, vecRightTop, this](Touch *touch, Event *event)->void{
        Vec2 prev = event->getCurrentTarget()->getPosition();
        Vec2 delta =touch->getDelta();
        Vec2 shiftPosition = delta+prev;
        this->setPosition(shiftPosition.getClampPoint(vecLeftBottom,vecRightTop));
    };
    touchListener->onTouchBegan = [](Touch *touch, Event *event)->bool{return true;};
    touchListener->onTouchMoved = onTouchMoved;//CC_CALLBACK_2(MPlayer::onTouchMoved, this);
    touchListener->onTouchEnded = [](Touch *touch, Event *event)->void{};
    touchListener->onTouchCancelled = [](Touch *touch, Event *event)->void{};
    
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}