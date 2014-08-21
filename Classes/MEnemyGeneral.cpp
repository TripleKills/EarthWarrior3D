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

MEnemyGeneral::MEnemyGeneral() : _timePassed(0.0f), _interval(0.5f), _timeInterval(0.0f){
}

void MEnemyGeneral::destroy() {
    if (nullptr != _sInstance) {
        CC_SAFE_DELETE(_sInstance);
    }
}

void MEnemyGeneral::update(float dt) {
    _timePassed += dt;
    if (_timeInterval == 0 or _timeInterval + dt >= _interval) {
        
    }
    _timeInterval += dt;
    _timeInterval = _timeInterval >= _interval ? _timeInterval - _interval : _timeInterval;
}