//
//  MWeapon2.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-19.
//
//

#ifndef EarthWarrior3D_MWeapon2_h
#define EarthWarrior3D_MWeapon2_h

#include "cocos2d.h"
#include "MMacros.h"


class MBullet2;
class MWeapon2;

class MWeaponLoader : public cocos2d::Ref {
public:
    CREATE_WITH_JSON(MWeaponLoader);
    cocos2d::Vector<MBullet2*> getBullets();
    void setTarget(cocos2d::Node* target) { this->_target = target;};
    void initWithJson(Json* document);
private:
    int _bulletNum;
    Json* doc;
    cocos2d::Node* _target;
};

class MWeaponEmitter : public cocos2d::Ref {
public:
    virtual void emmit(cocos2d::Vector<MBullet2*> bullets) = 0;
};

class MWeaponEmitterArc : public MWeaponEmitter {
public:
    CREATE_WITH_JSON(MWeaponEmitterArc);
    void initWithJson(Json* document) {};
    //static MWeaponEmitterArc* create();
    virtual void emmit(cocos2d::Vector<MBullet2*> bullets);
};

class MWeaponEmitterParallel : public MWeaponEmitter {
public:
    CREATE_WITH_JSON(MWeaponEmitterParallel);
    void initWithJson(Json* document) {};
   // static MWeaponEmitterParallel* create();
    virtual void emmit(cocos2d::Vector<MBullet2*> bullets);
};

class MWeapon2 : public cocos2d::Node {
public:
   // static MWeapon2* create();
    CREATE_WITH_JSON(MWeapon2);
    void initWithJson(Json* document);
    
    virtual void onEnter();
   // MWeapon2():_timePassed(-1.0f), _interval(0.0f) {};
    void update(float dt);
    void setEmitter(MWeaponEmitter* emitter);
    MWeaponEmitter* getEmitter() {return _emitter;}
    void setLoader(MWeaponLoader* loader);
    MWeaponLoader* getLoader() { return _loader; };
    void setBulletsLayer(cocos2d::Node* layer);
    CC_SYNTHESIZE(float, _interval, Interval);
    
    CC_SYNTHESIZE(MWeapon2*, _parent, ParentWeapon);
    void enableGroupFire() {_groupTimePassed = 0.0f;};
    bool canFireInGroup() {return _groupTimePassed < _groupFireTime;};
    void addChildWeapon(MWeapon2* child);
private:
    MWeaponLoader* _loader;
    MWeaponEmitter* _emitter;
    float _timePassed, _groupFireTime, _groupTimePassed;
    cocos2d::Vector<MWeapon2*> _weapons;
    cocos2d::Node* _bulletsLayer;
};


#endif