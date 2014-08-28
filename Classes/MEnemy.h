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

#include "MAirCraft.h"

#define CREATE_WITH_JSON(__TYPE__) \
public:\
    static __TYPE__* createWithJson(const char* fileName) {\
        auto enemy = new __TYPE__();\
        enemy->initWithJsonFile(fileName);\
        enemy->autorelease();\
        return enemy;\
    }\
    static __TYPE__* createWithJson(rapidjson::Document& document) {\
        auto enemy = new __TYPE__();\
        enemy->initWithJson(document);\
        enemy->autorelease();\
        return enemy;\
    }\

class MEnemy : public MAirCraft {
public:
    void onEnter();
    
protected:
    virtual void initWithJson(rapidjson::Document& document)=0;
    void initWithJsonFile(const char* fileName);
};

class MEnemyLine : public MEnemy {
public:
    CREATE_WITH_JSON(MEnemyLine);
    virtual void update(float dt);
protected:
    void initWithJson(rapidjson::Document& document) { MEnemy::initWithJson(document);};
private:
    MEnemyLine(){};
};

class MEnemyArc : public MEnemy {
public:
    CREATE_WITH_JSON(MEnemyArc);
    virtual void update(float dt);
    CC_SYNTHESIZE(float, _rotateSpeed, RotateSpeed);
    void print();
protected:
    MEnemyArc(){};
    void initWithJson(rapidjson::Document& document);
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
    virtual void initWithJson(rapidjson::Document& document);
protected:
    cocos2d::Vec2 _center;
};

class MEnemyStaticAimTarget : public MEnemy {
public:
    static MEnemyStaticAimTarget* create(cocos2d::Node* target);
    CC_SYNTHESIZE(cocos2d::Node*, _target, Target);
    virtual void update(float dt);
protected:
    void initWithJson(rapidjson::Document& document) { MEnemy::initWithJson(document);};
};

#endif
