//
//  MLoadingScene.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-15.
//
//

#ifndef EarthWarrior3D_MLoadingScene_h
#define EarthWarrior3D_MLoadingScene_h

#include "cocos2d.h"

class MLoadingScene : public cocos2d::Layer {
public:
    MLoadingScene();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MLoadingScene);
    virtual bool init();
private:
    void initLayer();
    void initCoco();
    void loadResources();
    void loadMusic();
    void loadParticle();
    void loadPicture();
    void onPictureLoad(cocos2d::Ref* sender);
    void setPercent(int percent);
    void toNextScene();

private:
    int _picNum, _curNum;
    cocos2d::Label* _percent;
    cocos2d::Sprite* _progress;
};

#endif
