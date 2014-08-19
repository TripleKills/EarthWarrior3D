//
//  MEnemy.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-19.
//
//

#ifndef EarthWarrior3D_MEnemy_h
#define EarthWarrior3D_MEnemy_h

#include "cocos2d.h"

#include "MAirCraft.h"

class MEnemy : public MAirCraft {
public:
    void onEnter();
};

class MEnemyLine : public MEnemy {
public:
    static MEnemyLine* create(float speed);
    virtual void update(float dt);
    CC_SYNTHESIZE(float, _speed, Speed);
};

class MEnemyArc : public MEnemy {
public:
    static MEnemyArc* create(float speed, float rotateSpeed);
    virtual void update(float dt);
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(float, _rotateSpeed, RotateSpeed);
};

#endif
