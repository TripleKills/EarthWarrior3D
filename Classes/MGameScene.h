//
//  MGameScene.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MGameScene_h
#define EarthWarrior3D_MGameScene_h

#include "cocos2d.h"

class MGameScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MGameScene);
    
    virtual bool init();
};


#endif
