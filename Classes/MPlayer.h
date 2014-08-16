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

class MPlayer : public MAirCraft {
public:
    CREATE_FUNC(MPlayer);
    
    virtual bool init();
    
    virtual void onEnter();
    
private:
    void initTouchEvent();
};

#endif
