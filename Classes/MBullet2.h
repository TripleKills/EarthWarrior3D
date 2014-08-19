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
#include "MBulletAimer.h"
#include "MBulletRunner.h"

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
    CC_SYNTHESIZE(int, _speed, Speed);
    
    MBulletAimer* getAimer() { return _aimer; };
    void setAimer(MBulletAimer* aimer) {
        this->_aimer = aimer;
        this->_aimer->retain();
        this->_aimer->setOwner(this);
    };
    void setRunner(MBulletRunner* runner) {
        this->_runner = runner;
        this->_runner->retain();
        this->_runner->setOwner(this);
    };
protected:
    MBulletAimer* _aimer;
    MBulletRunner* _runner;
    float _timePassed;
};

#endif
