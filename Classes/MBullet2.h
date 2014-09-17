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
    template<typename T> void initWithJson(T& document);
    
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
    template<typename T> void initWithJson(T& document);
    virtual void update(float dt);
};

class MBulletAimerTargeted : public MBulletAimer {
public:
    CREATE_WITH_JSON(MBulletAimerTargeted);
    template<typename T> void initWithJson(T& document);
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
    template<typename T> void initWithJson(T& document) {};
    virtual void update(float dt);
};

class MBulletRunnerTarget : public MBulletRunner {
public:
    CREATE_WITH_JSON(MBulletRunnerTarget);
    template<typename T> void initWithJson(T& document);
    virtual void update(float dt);
    void setTarget(cocos2d::Node* target) { this->_target = target;};
private:
    std::string _targetType;
    cocos2d::Node* _target;
};

template<typename T> void MBullet2::initWithJson(T& document){
    MGameEntity::initWithJson(document);
    _damage = document["damage"].GetInt();
    _owner = entityTypes::kNone;
    
    _runner = nullptr;
    rapidjson::Value &runner = document["runner"];
    std::string runnerType = runner["type"].GetString();
    MBulletRunner* mrunner = nullptr;
    if (runnerType == "line") {
        mrunner = MBulletRunnerLine::createWithJson(runner);
    } else if (runnerType == "targeted") {
        mrunner = MBulletRunnerTarget::createWithJson(runner);
    }
    setRunner(mrunner);
    
    _aimer = nullptr;
    if (document.HasMember("aimer")) {
        rapidjson::Value &aimer = document["aimer"];
        std::string type = aimer["type"].GetString();
        MBulletAimer* maimer = nullptr;
        if (type == "static") {
            maimer = MBulletAimerStatic::createWithJson(aimer);
        } else if (type == "targeted") {
            maimer = MBulletAimerTargeted::createWithJson(aimer);
        }
        setAimer(maimer);
    }
    
    
    _timePassed = 0;
};

template<typename T> void MBulletAimerStatic::initWithJson(T& document) {
    float time = document["time"].GetDouble();
    CCLOG("MBulletAimerStatic set time to %f", time);
    setTime(time);
    CCLOG("MBulletAimerStatic time is %f", getTime());
}

template<typename T> void MBulletAimerTargeted::initWithJson(T& document) {
    float time = document["time"].GetDouble();
    setTime(time);
    _targetType = document["target"].GetString();
    _target = nullptr;
}

template<typename T> void MBulletRunnerTarget::initWithJson(T& document) {
    _targetType = document["target"].GetString();
    _target = nullptr;
}

#endif
