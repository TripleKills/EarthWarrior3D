//
//  MEnemyGeneral.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-21.
//
//

#ifndef EarthWarrior3D_MEnemyGeneral_h
#define EarthWarrior3D_MEnemyGeneral_h

#include "cocos2d.h"

class MEnemyMajor;
class MEnemyColonel;
class MEnemyColonelConscripter;
class MEnemyColonelDeployer;

/**
 *1. general
 *2. major
 *3. colonel
 */

class MEnemyGeneral {
public:
    static MEnemyGeneral* getInstance() {
        if (nullptr == _sInstance) {
            _sInstance = new MEnemyGeneral();
        }
        return _sInstance;
    };
    
    void destroy();
    void update(float dt);
    CC_SYNTHESIZE(float, _interval, Interval);
private:
    MEnemyGeneral();
    static MEnemyGeneral* _sInstance;
    float _timePassed, _timeInterval;
};

/**
 * a major control one wave of attack
 * time: the time this wave attacks, -1 for loop, other for real time
 * when times over, the major will control all ships fly to out of the screen
 * bottom straight
 */
class MEnemyMajor : public cocos2d::Ref {
public:
    CREATE_FUNC(MEnemyMajor);
    bool init();
private:
    float _time;
    cocos2d::Vector<MEnemyColonel*> _colonels;
};

/**
 * a colonel control one force, the force can only have one member
 * interval: the interval the force reapear, -1 for only once, other for real time
 */
class MEnemyColonel : public cocos2d::Ref {
public:
    CREATE_FUNC(MEnemyColonel);
    bool init();
private:
    float _interval;
};

class MEnemyColonelConscripter {};

class MEnemyColonelDeployer {};


#endif
