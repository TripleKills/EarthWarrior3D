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
    MWeaponLoader(): _bulletNum(0) {};
    static MWeaponLoader* create(int bulletNum);
    cocos2d::Vector<MBullet2*> getBullets();
    void setTarget(cocos2d::Node* target) { this->_target = target;};
private:
    int _bulletNum;
    cocos2d::Node* _target;
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

class MWeapon2 : public cocos2d::Node {
public:
    static MWeapon2* create();
    virtual void onEnter();
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