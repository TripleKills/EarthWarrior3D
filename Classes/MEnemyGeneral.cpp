//
//  MEnemyGeneral.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-21.
//
//

#include "MEnemyGeneral.h"

USING_NS_CC;

MEnemyGeneral* MEnemyGeneral::_sInstance = nullptr;

MEnemyGeneral::MEnemyGeneral() : _timePassed(0.0f), _interval(0.5f),
                                _timeInterval(0.0f), _mMajors(){
                                    init();
}

void MEnemyGeneral::init() {
}

MEnemyGeneral::~MEnemyGeneral() {
    _mMajors.clear();
}

void MEnemyGeneral::destroy() {
    if (nullptr != _sInstance) {
        CC_SAFE_DELETE(_sInstance);
    }
}

void MEnemyGeneral::update(float dt) {
    _timePassed += dt;
    if (_timeInterval == 0 or _timeInterval + dt >= _interval) {
        auto major = _mMajors.back();
        float subDt = _timeInterval == 0 ? dt : _timeInterval + dt;
        if (!major->update(subDt)) {
            _mMajors.popBack();
        }
    }
    _timeInterval += dt;
    _timeInterval = _timeInterval >= _interval ? _timeInterval - _interval : _timeInterval;
}

MEnemyMajor::MEnemyMajor() : _time(-1), _colonels(), _timePassed(0.0f) {
    
}

bool MEnemyMajor::init() {
    return true;
}

bool MEnemyMajor::update(float dt) {
    _timePassed += dt;
    
    if (_time != MEnemyMajor::K_LOOP_INTERVAL && _timePassed >= _time) {
        bool ret = false;
        for(int i = _colonels.size()-1; i >= 0; i-- ) {
            auto colonel = _colonels.at(i);
            if (colonel->flee(dt)) {
                ret = true;
            } else {
                _colonels.erase(i);
            }
        }
        return ret;
    }
    
    
    bool result = false;
    for(int i = _colonels.size()-1; i >= 0; i-- ) {
        auto colonel = _colonels.at(i);
        bool ret = colonel->update(dt);
        
        bool isLoop = colonel->getInterval() == MEnemyColonel::K_LOOP_INTERVAL;
        if (!ret && !isLoop) {
            _colonels.erase(i);
        } else if (ret) {
            result = true;
        }
    }
    return result;
}

void MEnemyMajor::activate() {
}



bool MEnemyColonel::init() {
    return true;
}

bool MEnemyColonel::flee(float dt) {
    return true;
}

void MEnemyColonel::activate() {
}

bool MEnemyColonel::update(float dt) {
    return true;
}
