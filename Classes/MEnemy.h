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
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "MAirCraft.h"

class MEnemy : public MAirCraft {
public:
    void onEnter();
};

class MEnemyLine : public MEnemy {
public:
    static MEnemyLine* createWithJson(rapidjson::Document& document);
    static MEnemyLine* createWithJson(const char* fileName);
    virtual void update(float dt);
    void print();
private:
    void initWithJson(rapidjson::Document& document);
    void initWithJson(const char* fileName);
    MEnemyLine(){};
};

class MEnemyArc : public MEnemy {
public:
    static MEnemyArc* create(float speed, float rotateSpeed);
    virtual void update(float dt);
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(float, _rotateSpeed, RotateSpeed);
};

class MEnemyRound : public MEnemy {
public:
    static MEnemyRound* create(float radius, float rotateSpeed);
    virtual void update(float dt);
    virtual void onEnter();
    CC_SYNTHESIZE(float, _radius, Radius);
    CC_SYNTHESIZE(float, _rotateSpeed, RotateSpeed);
protected:
    cocos2d::Vec2 _center;
};

class MEnemyStaticAimTarget : public MEnemy {
public:
    static MEnemyStaticAimTarget* create(cocos2d::Node* target);
    CC_SYNTHESIZE(cocos2d::Node*, _target, Target);
    virtual void update(float dt);
};

#endif
