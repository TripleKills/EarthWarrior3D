//
//  MMainScene.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-14.
//
//

#include "MMainScene.h"
//#include "MMacros.h"

USING_NS_CC;

Scene* MMainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MMainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MMainScene::init() {
    if (!Layer::init())
        return false;
    
//    auto startNormal = Sprite::create("start_game.png");
//    auto startPressed = Sprite::create("start_game.png");
//    auto startMenu = MenuItemSprite::create(startNormal, startPressed, CC_CALLBACK_1(MMainScene::startGame, this));
//    startMenu->setPosition(Vec2(0, 200));
//    
//    auto exitNormal = Sprite::create("license.png");
//    auto exitPressed = Sprite::create("license.png");
//    auto exitMenu = MenuItemSprite::create(exitNormal, exitPressed, CC_CALLBACK_1(MMainScene::startGame, this));
//    exitMenu->setPosition(Vec2(0, -200));
//    
//    auto menu = Menu::create(startMenu, exitMenu, NULL);
//    auto origin = Director::getInstance()->getVisibleOrigin();
//    auto size = Director::getInstance()->getVisibleSize();
//    menu->setPosition(origin + (size / 2));
//    
//    addChild(menu);
    return true;
}

/**
void MMainScene::startGame(Ref* sender) {
    LOG_FUNC
}

void MMainScene::exitGame(Ref* sender) {
    LOG_FUNC
}
*/