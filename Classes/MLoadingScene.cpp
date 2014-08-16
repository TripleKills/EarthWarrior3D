//
//  MLoadingScene.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MLoadingScene.h"
#include "MMacros.h"
#include "MStringUtils.h"
#include "MParticleManager.h"
#include "MGameScene.h"

USING_NS_CC;

MLoadingScene::MLoadingScene(): _picNum(0), _curNum(0) {
};

Scene* MLoadingScene::createScene() {
    auto scene = Scene::create();
    auto layer = MLoadingScene::create();
    scene->addChild(layer);
    return scene;
}

bool MLoadingScene::init() {
    if (!Layer::init())
        return false;
    this->initLayer();
    this->loadResources();
    return true;
}

void MLoadingScene::initLayer() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loadingAndHP.plist");
    
    auto bg = Sprite::createWithSpriteFrameName("loading_bk.png");
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(bg);
    
    _percent = Label::createWithBMFont("num.fnt", "0%");
    _percent->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 170));
    this->addChild(_percent);
    
    _progress = Sprite::createWithSpriteFrameName("loading_progress_thumb.png");
    _progress->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 320));
    this->addChild(_progress);
    
    this->setPercent(0);

    auto progressBg = Sprite::createWithSpriteFrameName("loading_progress_bk.png");
    progressBg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 300));
    this->addChild(progressBg);

    initCoco();
}

void MLoadingScene::initCoco() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto coco = Sprite3D::create("coconut.c3b", "coco.png");
    coco->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 150));
    coco->setRotation3D(Vec3(-90,0,0));
    this->addChild(coco);
    
    auto action = RepeatForever::create(RotateBy::create(0.8f, Vec3(0,360,0)));
    coco->runAction(action);
}

void MLoadingScene::loadResources() {
    this->loadMusic();
    this->loadParticle();
    this->loadPicture();
}

void MLoadingScene::loadMusic() {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    std::string effects[4] = {"explodeEffect.mp3", "hit.mp3", "boom2.mp3", "boom.mp3"};
    for(int i = 0; i < 4; i++) {
        CCLOG("preload effect %s", effects[i].c_str());
        audio->preloadEffect(effects[i].c_str());
    }
    audio->preloadBackgroundMusic("Orbital Colossus_0.mp3");
    audio->playBackgroundMusic("Flux2.mp3");
}

void MLoadingScene::loadParticle() {
    std::string plists[9] = {"flare.plist",  "glow.plist",  "debris.plist",  "emissionPart.plist",  "engine.plist",
        "missileFlare.plist",  "emission.plist",  "missileFlare.plist",  "toonSmoke.plist"};
    for(int i = 0; i < 9; i++) {
        std::string str = MStringUtils::removeDirAndReplacePostfix(plists[i].c_str(), "");
        MParticleManager::getInstance()->addParticle(plists[i].c_str(), str.c_str());
    }
}

void MLoadingScene::loadPicture() {
    std::string pictures[13] = {"boss.png", "groundLevel.jpg", "coco.png", "bullets.png",
        "daodan_32.png", "diji02_v002_128.png", "dijiyuanv001.png", "playerv002_256.png",
        "streak.png", "gameover_score_num_0.png", "num_0.png", "score_right_top.png",
        "gameover.png"};
    _picNum = 13;
    auto textureCache = TextureCache::getInstance();
    for(int i = 0; i < 13; i++) {
        CCLOG("preload effect %s", pictures[i].c_str());
        textureCache->addImageAsync(pictures[i], CC_CALLBACK_1(MLoadingScene::onPictureLoad, this));
    }
}

void MLoadingScene::onPictureLoad(Ref* sender) {
    _curNum++;
    int percent = (int) (_curNum * 100 / _picNum);
    setPercent(percent);
    if (percent == 100) {
        this->toNextScene();
    }
}

void MLoadingScene::toNextScene() {
    LOG_FUNC
    auto scene = MGameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MLoadingScene::setPercent(int percent) {
    char tmp[10];
    sprintf(tmp, "%d%%", percent);
    _percent->setString(tmp);
    
    auto contentSize = _progress->getContentSize();
    float startPoint = contentSize.width / 2;
    float endPoint = Director::getInstance()->getVisibleSize().width - contentSize.width / 2;
    float dis = endPoint - startPoint;
    float x = startPoint + dis * percent / 100;
    float y = _progress->getPosition().y;
    _progress->setPosition(Vec2(x,y));
}