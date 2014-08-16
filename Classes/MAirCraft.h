//
//  MAirCraft.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MAirCraft_h
#define EarthWarrior3D_MAirCraft_h

#include "cocos2d.h"
#include "MGameEntity.h"

class MAirCraft : public MGameEntity {
public:
    CREATE_FUNC(MAirCraft);
    virtual bool init();
};

#endif
