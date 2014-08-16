//
//  MParticleManager.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MParticleManager_h
#define EarthWarrior3D_MParticleManager_h

#include "cocos2d.h"
#include <map>

class MParticleManager {
public:
    static MParticleManager* getInstance() {
        if (_sInstance == nullptr) {
            _sInstance = new MParticleManager();
        }
        return _sInstance;
    };
    
    void addParticle(const char* file, const char* name);
    cocos2d::ValueMap getParticle(const char* name);
private:
    
    class MCGarbo {
    public:
        ~MCGarbo() {
            if (MParticleManager::_sInstance != nullptr) {
                CC_SAFE_DELETE(MParticleManager::_sInstance);
            }
        }
    };
    
    
    MParticleManager();
    
    std::map<std::string, cocos2d::ValueMap> m_plistMap;
    static MParticleManager* _sInstance;
    static MCGarbo _garbo;
};

#endif
