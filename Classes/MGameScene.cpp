//
//  MGameScene.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MGameScene.h"

USING_NS_CC;

Scene* MGameScene::createScene() {
    auto scene = Scene::create();
    auto layer = MGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool MGameScene::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}