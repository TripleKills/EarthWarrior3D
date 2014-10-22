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
#include "MEnemy.h"
#include "MMacros.h"
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
    
    ~MEnemyGeneral();
    
    void destroy();
    void update(float dt);
    CC_SYNTHESIZE(float, _interval, Interval);
private:
    MEnemyGeneral();
    void init();
    
private:
    static MEnemyGeneral* _sInstance;
    float _timePassed, _timeInterval;
    cocos2d::Vector<MEnemyMajor*> _mMajors;
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
    MEnemyMajor();
    bool init();
    bool update(float dt);
    void activate();
public:
    constexpr const static float K_LOOP_INTERVAL = -1;
private:
    float _time, _timePassed;
    cocos2d::Vector<MEnemyColonel*> _colonels;
};

/**
 * a colonel control one force, the force can only have one member
 * interval: the interval the force reapear, -1 for only once, other for real time
 */
class MEnemyColonel : public cocos2d::Ref {
public:
    CREATE_WITH_JSON(MEnemyColonel);
    ~MEnemyColonel();
    bool init();
    bool update(float dt);
    void activate();
    bool isLoop();
    bool flee(float dt);
protected:
    virtual void initWithJson(Json* document);
private:
    void launchAForce();
public:
    constexpr const static float K_ONCE_INTERVAL = -1;
private:
    float _interval, _timePassed, _fleeSpeed;
    MEnemyColonelConscripter* _conscripter;
    MEnemyColonelDeployer* _deployer;
    cocos2d::Vector<MEnemy*> _mSoldiers;
};

class MEnemyColonelConscripter : public cocos2d::Ref {
public:
    CREATE_WITH_JSON(MEnemyColonelConscripter);
    bool init();
    void conscript(cocos2d::Vector<MEnemy*>& enemies);
protected:
    virtual void initWithJson(Json* document);
private:
    Json* _enemyJson;
};

class MEnemyColonelDeployer : public cocos2d::Ref {
public:
    CREATE_WITH_JSON(MEnemyColonelDeployer);
    bool init();
    void deployEnemys(cocos2d::Vector<MEnemy*>& enemys);
protected:
    MEnemyColonelDeployer() : _posJson(nullptr) {};
    virtual void initWithJson(Json* document);
private:
    Json* _posJson;
};


#endif
