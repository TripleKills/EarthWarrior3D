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
#include "spine/Json.h"
#include "MAirCraft.h"

#include "MMacros.h"

class MEnemy : public MAirCraft {
public:
    void onEnter();
protected:
    virtual void initWithJson(Json* document);
};

class MEnemyLine : public MEnemy {
public:
    CREATE_WITH_JSON(MEnemyLine);
    virtual void update(float dt);
};

class MEnemyArc : public MEnemy {
public:
    CREATE_WITH_JSON(MEnemyArc);
    virtual void update(float dt);
    CC_SYNTHESIZE(float, _rotateSpeed, RotateSpeed);
    virtual void print();
   
protected:
    virtual void initWithJson(Json* document);
};

class MEnemyRound : public MEnemy {
public:
    CREATE_WITH_JSON(MEnemyRound);
    void print();
    virtual void update(float dt);
    virtual void onEnter();
    CC_SYNTHESIZE(float, _radius, Radius);
    CC_SYNTHESIZE(float, _rotateSpeed, RotateSpeed);
protected:
    virtual void initWithJson(Json* document);
protected:
    cocos2d::Vec2 _center;
};

class MEnemyStaticAimTarget : public MEnemy {
public:
    CREATE_WITH_JSON(MEnemyStaticAimTarget);
    CC_SYNTHESIZE(cocos2d::Node*, _target, Target);
    virtual void update(float dt);
protected:
    void initWithJson(Json* document);
};

#endif
