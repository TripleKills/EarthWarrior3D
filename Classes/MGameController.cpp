//
//  MGameController.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-9-2.
//
//

#include "MGameController.h"
#include "MEventData.h"
USING_NS_CC;

MGameController* MGameController::_sInstance = nullptr;

Vector<MGameEntity*> MGameController::_aliveEnemys;

MGameController::MGameController(){
    _player = nullptr;
    registerEvents();
}

MGameController::~MGameController() {
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeCustomEventListeners("entity_go_out");
}

void MGameController::registerEvents() {
    CCLOG("register events");
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    EventListenerCustom* entityGoOutScreen = EventListenerCustom::create("entity_go_out",
                                                                         CC_CALLBACK_1( MGameController::onEntityGoOutScreen, this));
    dispatcher->addEventListenerWithFixedPriority(entityGoOutScreen, 1);
}

void MGameController::onEntityGoOutScreen(cocos2d::EventCustom* event) {
    CCLOG("entity go out");
    MEventData* data = static_cast<MEventData*>(event->getUserData());
    ValueMap* vm = data->map;
    int s = (*vm)["seconds"].asInt();
    CCLOG("seconds is %d", s);
    //CC_SAFE_DELETE(data);
}