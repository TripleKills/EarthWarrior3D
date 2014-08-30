//
//  MPlayer.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MPlayer_h
#define EarthWarrior3D_MPlayer_h

#include "cocos2d.h"
#include "MAirCraft.h"
#include "MMacros.h"
class MPlayer : public MAirCraft {
public:
    CREATE_WITH_JSON(MPlayer);

    virtual void onEnter();
    
    virtual void onHurt(int damage, cocos2d::Vec2 position) {};
    virtual void onDead() {};
    
private:
    void initTouchEvent();
};

#endif
