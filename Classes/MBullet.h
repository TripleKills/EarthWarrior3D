//
//  MBullet.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

//TODO deprecated
#ifndef EarthWarrior3D_MBullet_h
#define EarthWarrior3D_MBullet_h

#include "cocos2d.h"

#include "MGameEntity.h"

class MBullet : public MGameEntity {
public:
    MBullet();
    
    CREATE_FUNC(MBullet);
    virtual bool init();
    
    virtual void onEnter();
    
    void reset();
    
    cocos2d::Vec2 getSpeed() {return _speed;}
    void setSpeed(cocos2d::Vec2 speed);

    CC_SYNTHESIZE(int, _owner, Owner);
    CC_SYNTHESIZE(int, _damage, Damage);
protected:
    cocos2d::Vec2 _speed;
};

class MLineBullet : public MBullet {
public:
    CREATE_FUNC(MLineBullet);
    virtual bool init();
    virtual void update(float dt);
};

class MLineBackBullet : public MLineBullet {
public:
    MLineBackBullet();
    CREATE_FUNC(MLineBackBullet);
    virtual bool init();
    virtual void update(float dt);
    
    void setDistX(float distX);
    virtual void reset();
private:
    float _distX;
};

#endif
