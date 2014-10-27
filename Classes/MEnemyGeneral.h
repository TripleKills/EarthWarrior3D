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
    void initWithJson(Json* document);
    void destroy();
    void update(float dt);
private:
    MEnemyGeneral();
    
private:
    static MEnemyGeneral* _sInstance;
    float _timePassed;
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
    CREATE_WITH_JSON(MEnemyMajor);
    bool update(float dt);
    void activate();
    
protected:
    virtual void initWithJson(Json* document);
    
private:
    MEnemyMajor() : _time(-1), _timePassed(0), _colonels() {};
    
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
    void registerEvents();
    void unregisterEvents();
    bool update(float dt);
    void activate();
    bool isLoop();
    bool flee(float dt);
    void setFirstDelay(float delay) {_delayTimePassed = - delay;};
protected:
    virtual void initWithJson(Json* document);
    void checkSolderFleeOrDead(cocos2d::EventCustom* event);
private:
    void launchAForce();
public:
    constexpr const static float K_ONCE_INTERVAL = -1;
private:
    MEnemyColonel();
    
    float _interval, _timePassed, _fleeSpeed, _delayTimePassed;
    MEnemyColonelConscripter* _conscripter;
    MEnemyColonelDeployer* _deployer;
    cocos2d::Vector<MEnemy*> _mSoldiers;
};

class MEnemyColonelConscripter : public cocos2d::Ref {
public:
    CREATE_WITH_JSON(MEnemyColonelConscripter);
    void conscript(cocos2d::Vector<MEnemy*>& enemies);
protected:
    virtual void initWithJson(Json* document);
private:
    MEnemyColonelConscripter() : _enemyJson(nullptr) {};
    Json* _enemyJson;
};

class MEnemyColonelDeployer : public cocos2d::Ref {
public:
    CREATE_WITH_JSON(MEnemyColonelDeployer);
    void deployEnemys(cocos2d::Vector<MEnemy*>& enemys);
protected:
    MEnemyColonelDeployer() : _posJson(nullptr) {};
    virtual void initWithJson(Json* document);
private:
    Json* _posJson;
};


#endif
