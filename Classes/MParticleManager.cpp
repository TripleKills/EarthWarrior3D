//
//  MParticleManager.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MParticleManager.h"

USING_NS_CC;

MParticleManager* MParticleManager::_sInstance = NULL;
MParticleManager::MCGarbo MParticleManager::_garbo;

MParticleManager::MParticleManager() : m_plistMap() {
    m_plistMap.clear();
}

void MParticleManager::addParticle(const char* file, const char* name) {
    CCLOG("add particle %s, %s", file, name);
    std::map<std::string, ValueMap>::iterator ite = m_plistMap.begin();
    ValueMap data = FileUtils::getInstance()->getValueMapFromFile(file);
    m_plistMap.insert(ite, make_pair(name, data));
}

ValueMap MParticleManager::getParticle(const char* name) {
    return m_plistMap.find(name)->second;
}