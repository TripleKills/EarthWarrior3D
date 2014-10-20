//
//  MBullet2.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-18.
//
//

#ifndef EarthWarrior3D_MBullet2_h
#define EarthWarrior3D_MBullet2_h

#include "cocos2d.h"

#include "MGameEntity.h"
#include "MMacros.h"
#include "spine/Json.h"
class MBulletAimer;
class MBulletRunner;

class MBullet2 : public MGameEntity {
public:
    CREATE_WITH_JSON(MBullet2);
    virtual void print();
    
    virtual void onEnter();
    void update(float dt);
    
    void reset();

    CC_SYNTHESIZE(int, _owner, Owner);
    CC_SYNTHESIZE(int, _damage, Damage);
    
    MBulletAimer* getAimer() { return _aimer; };
    void setAimer(MBulletAimer* aimer);
    void setRunner(MBulletRunner* runner);

protected:
    void initWithJson(Json* document);
    
protected:
    MBulletAimer* _aimer;
    MBulletRunner* _runner;
    float _timePassed;
};

class MBulletAimer : public cocos2d::Ref {
public:
    CC_SYNTHESIZE(float, time, Time);
    CC_SYNTHESIZE(MBullet2*, _owner, Owner);
    virtual void update(float dt) = 0;
};

class MBulletAimerStatic : public MBulletAimer {
public:
    CREATE_WITH_JSON(MBulletAimerStatic);
    void initWithJson(Json* document);
    virtual void update(float dt);
};

class MBulletAimerTargeted : public MBulletAimer {
public:
    CREATE_WITH_JSON(MBulletAimerTargeted);
    void initWithJson(Json* document);
    virtual void update(float dt);
private:
    std::string _targetType;
    cocos2d::Node* _target;
};

class MBulletRunner : public cocos2d::Ref {
public:
    virtual void update(float dt) = 0;
    CC_SYNTHESIZE(MBullet2*, _owner, Owner);
};

class MBulletRunnerLine : public MBulletRunner {
public:
    CREATE_WITH_JSON(MBulletRunnerLine);
    void initWithJson(Json* document) {};
    virtual void update(float dt);
};

class MBulletRunnerTarget : public MBulletRunner {
public:
    CREATE_WITH_JSON(MBulletRunnerTarget);
    void initWithJson(Json* document);
    virtual void update(float dt);
    void setTarget(cocos2d::Node* target) { this->_target = target;};
private:
    std::string _targetType;
    cocos2d::Node* _target;
};



#endif
