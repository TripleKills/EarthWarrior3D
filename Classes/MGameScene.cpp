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
#include "MBullet2.h"
#include "MWeapon2.h"
#include "MEnemy.h"
#include "MEnemyGeneral.h"
#include "MAirCraft.h"
#include "MJsonUtils.h"
#include "MGameController.h"

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
    
    auto player = MPlayer::createWithJson("configuration/one.json");
    addChild(player);
    CCLOG("player typeid is %s", typeid(player).name());
    MGameController::getInstance()->setPlayer(player);
    player->setPosition(Vec2(200, 100));

    auto target = Sprite3D::create("playerv002.c3b", "playerv002_256.png");
    this->addChild(target);
    target->setScale(5);
    target->setPosition(Vec2(0, 900));
    auto seq = Sequence::create(MoveBy::create(4.0, Vec2(640, 0)),
                                               MoveBy::create(4.0, Vec2(-640,0)),nullptr);
    auto repeat = RepeatForever::create(seq);
    target->runAction(repeat);

    
    auto _weapon = MWeapon2::create();
    auto loader = MWeaponLoader::create(1);
    auto emitter = MWeaponEmitterArc::create();
    loader->setTarget(target);
    _weapon->setBulletsLayer(this);
    _weapon->setLoader(loader);
    _weapon->setInterval(1);
    _weapon->setEmitter(emitter);
    _weapon->setPosition(Vec2(-75, 40));
    player->addChild(_weapon);
    
    auto _weapon2 = MWeapon2::create();
    auto loader2 = MWeaponLoader::create(1);
    loader2->setTarget(target);
    auto emitter2 = MWeaponEmitterArc::create();
    _weapon2->setBulletsLayer(this);
    _weapon2->setLoader(loader2);
    _weapon2->setInterval(1);
    _weapon2->setEmitter(emitter2);
    _weapon2->setPosition(Vec2(40, 40));
    //player->addChild(_weapon2);
    
    //auto enemy = MEnemyStaticAimTarget::create(player);
    //enemy->setRotation(180);
    //addChild(enemy);
    //enemy->setPosition(Vec2(320, 700));
    
    auto air = MEnemyRound::createWithJson("configuration/one.json");
    addChild(air);
    air->setPosition(Vec2(300,200));
    air->print();
    MGameController::_aliveEnemys.pushBack(air);
    
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