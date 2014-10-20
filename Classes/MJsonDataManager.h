//
//  MJsonDataManager.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-10-20.
//
//

#ifndef EarthWarrior3D_MJsonDataManager_h
#define EarthWarrior3D_MJsonDataManager_h

#include "cocos2d.h"
#include "MJsonUtils.h"

class MJsonDataManager {
public:
    ~MJsonDataManager(){};
    
    static MJsonDataManager* getInstance() {
        if (_sInstance == nullptr) {
            _sInstance = new MJsonDataManager();
        }
        return _sInstance;
    }
    void destory() {
        CC_SAFE_DELETE(_sInstance);
    }
    void load();
    void hasMember(const char* m) {
        CCLOG("has member in mgr %s, %d", m, JSON_DOC.HasMember(m) );
    };
private:
    static MJsonDataManager* _sInstance;
    MJsonDataManager() : JSON_DOC(){JSON_DOC.SetObject();};
public:
    rapidjson::Document JSON_DOC;
};

#endif
