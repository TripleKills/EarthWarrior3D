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

class MBullet2;
class MWeapon2;

class MWeaponLoader : public cocos2d::Ref {
public:
    static MWeaponLoader* create();
    cocos2d::Vector<MBullet2*> getBullets();
};

class MWeaponEmitter : public cocos2d::Ref {
public:
    virtual void emmit(cocos2d::Vector<MBullet2*> bullets) = 0;
};

class MWeaponEmitterArc : public MWeaponEmitter {
public:
    static MWeaponEmitterArc* create();
    virtual void emmit(cocos2d::Vector<MBullet2*> bullets);
};

class MWeapon2 : public cocos2d::Ref {
public:
    static MWeapon2* create();
    MWeapon2():_timePassed(-1.0f), _interval(0.0f) {};
    void update(float dt);
    void setEmitter(MWeaponEmitter* emitter);
    MWeaponEmitter* getEmitter() {return _emitter;}
    void setLoader(MWeaponLoader* loader);
    MWeaponLoader* getLoader() { return _loader; };
    void setBulletsLayer(cocos2d::Node* layer) { this->_bulletsLayer = layer;};
    CC_SYNTHESIZE(float, _interval, Interval);
private:
    MWeaponLoader* _loader;
    MWeaponEmitter* _emitter;
    float _timePassed;
    cocos2d::Node* _bulletsLayer;
};

#endif