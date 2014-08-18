//
//  MGameScene.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MGameScene.h"
#include "MLayerUtil.h"
#include "MGameEntity.h"
#include "MPlayer.h"
#include "MBullet.h"
#include "MBullet2.h"

USING_NS_CC;

#define BACKGROUND_SPEED 20

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
    this->initLayer();
    return true;
}

void MGameScene::initLayer() {
    MLayerUtil::addLayerSameZorderTag(SceneZOrder::bg_layer, SceneZOrder::ui_layer, this);
    auto gameLayer = this->getChildByTag(SceneZOrder::game_layer);
    MLayerUtil::addLayerSameZorderTag(GameZOrder::enemy_layer, GameZOrder::bullet_layer, gameLayer);
    auto bulletLayer = gameLayer->getChildByTag(GameZOrder::bullet_layer);
    MLayerUtil::addLayerSameZorderTag(BulletZOrder::player, BulletZOrder::enemy, bulletLayer);
    
    this->initBackground();
    
    auto player = MPlayer::create();
    addChild(player);
    player->setPosition(Vec2(200, 100));

    auto bullet = MBullet2::create();
    /**
    bullet->setOwner(entityTypes::kBullet);
    bullet->setSpeed(Vec2(60,300));
    bullet->setDamage(100);
    bullet->setDistX(100);
     */
    auto aimer = MBulletAimerTargeted::create(4, player);
    
    auto runner = MBulletRunnerLine::create();
    bullet->setRotation(-120);
    bullet->setSpeed(200);
    bullet->setDamage(100);
    bullet->setAimer(aimer);
    bullet->setRunner(runner);
    addChild(bullet);
    bullet->setPosition(Vec2(580,720));
}

void MGameScene::onEnter(){
    Layer::onEnter();
    
    scheduleUpdate();
}

void MGameScene::update(float dt) {
    updateBackground(dt);
}

void MGameScene::updateBackground(float dt) {
    _xScroll -= BACKGROUND_SPEED * dt;
    auto size = _background->getTexture()->getContentSize();
    auto rect = Rect(0, (int)_xScroll % (int)size.height, size.width, size.height/2);
    _background->setTextureRect(rect);
}

void MGameScene::initBackground(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _background = Sprite::create("groundLevel.jpg");
    Texture2D::TexParams texParams = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT};
    _background->getTexture()->setTexParameters(texParams);
    _background->setScale((float)visibleSize.width / (float)_background->getContentSize().width);
    _background->setAnchorPoint(Vec2(0.5, 0));
    _background->setPosition(Vec2(visibleSize.width/2, 0));
    auto bgLayer = this->getChildByTag(SceneZOrder::bg_layer);
    bgLayer->addChild(_background);
}