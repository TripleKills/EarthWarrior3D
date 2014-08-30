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
class MBulletAimer;
class MBulletRunner;

class MBullet2 : public MGameEntity {
public:
    MBullet2() : _timePassed(0.0f){};
    CREATE_FUNC(MBullet2);
    virtual bool init();
    virtual void onEnter();
    void update(float dt);
    
    void reset();

    CC_SYNTHESIZE(int, _owner, Owner);
    CC_SYNTHESIZE(int, _damage, Damage);
    
    MBulletAimer* getAimer() { return _aimer; };
    void setAimer(MBulletAimer* aimer);
    void setRunner(MBulletRunner* runner);
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
    static MBulletAimerStatic* create(float time);
    virtual void update(float dt);
};

class MBulletAimerTargeted : public MBulletAimer {
public:
    static MBulletAimerTargeted* create(float time, cocos2d::Node* target);
    virtual void update(float dt);
private:
    cocos2d::Node* _target;
};

class MBulletRunner : public cocos2d::Ref {
public:
    virtual void update(float dt) = 0;
    CC_SYNTHESIZE(MBullet2*, _owner, Owner);
};

class MBulletRunnerLine : public MBulletRunner {
public:
    static MBulletRunnerLine* create();
    virtual void update(float dt);
};

class MBulletRunnerTarget : public MBulletRunner {
public:
    static MBulletRunnerTarget* create();
    virtual void update(float dt);
    void setTarget(cocos2d::Node* target) { this->_target = target;};
private:
    cocos2d::Node* _target;
};


#endif
