//
//  MMainScene.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-14.
//
//

#ifndef EarthWarrior3D_MMainScene_h
#define EarthWarrior3D_MMainScene_h

#include "cocos2d.h"

class MMainScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(MMainScene);
    virtual bool init();
//private:
//    void startGame(cocos2d::Ref* sender);
//    void exitGame(cocos2d::Ref* sender);

};

#endif
