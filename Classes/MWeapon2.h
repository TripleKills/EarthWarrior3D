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
    template<typename T> void initWithJson(T& document);
private:
    int _bulletNum;
    rapidjson::Document doc;
    cocos2d::Node* _target;
};

class MWeaponEmitter : public cocos2d::Ref {
public:
    virtual void emmit(cocos2d::Vector<MBullet2*> bullets) = 0;
};

class MWeaponEmitterArc : public MWeaponEmitter {
public:
    CREATE_WITH_JSON(MWeaponEmitterArc);
    template<typename T> void initWithJson(T& document) {};
    //static MWeaponEmitterArc* create();
    virtual void emmit(cocos2d::Vector<MBullet2*> bullets);
};

class MWeaponEmitterParallel : public MWeaponEmitter {
public:
    CREATE_WITH_JSON(MWeaponEmitterParallel);
    template<typename T> void initWithJson(T& document) {};
   // static MWeaponEmitterParallel* create();
    virtual void emmit(cocos2d::Vector<MBullet2*> bullets);
};

class MWeapon2 : public cocos2d::Node {
public:
   // static MWeapon2* create();
    CREATE_WITH_JSON(MWeapon2);
    template<typename T> void initWithJson(T& document);
    
    virtual void onEnter();
   // MWeapon2():_timePassed(-1.0f), _interval(0.0f) {};
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

template<typename T> void MWeapon2::initWithJson(T& document) {
    this->_interval = document["fireInterval"].GetDouble();
    rapidjson::Value& loaderValue = document["loader"];
    auto loader = MWeaponLoader::createWithJson(loaderValue);
    setLoader(loader);
    rapidjson::Value& emitterValue = document["emitter"];
    std::string emitterType = emitterValue["type"].GetString();
    if (emitterType == "arc") {
        setEmitter(MWeaponEmitterArc::createWithJson(emitterValue));
    } else if (emitterType == "parallel") {
        setEmitter(MWeaponEmitterParallel::createWithJson(emitterValue));
    }
}

template<typename T> void MWeaponLoader::initWithJson(T& document) {
    this->_bulletNum = document["num"].GetInt();
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document["bullet"].Accept(writer);
    std::string reststring = buffer.GetString();
    doc.Parse<0>(reststring.c_str());
}
#endif