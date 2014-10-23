//
//  MJsonDataManager.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-10-20.
//
//

#include <stdio.h>
#include "MJsonDataManager.h"

MJsonDataManager* MJsonDataManager::_sInstance = nullptr;

MJsonDataManager::~MJsonDataManager(){
    for(auto iter = JSON_DOC.begin(); iter != JSON_DOC.end(); iter++) {
        Json* json = iter->second;
        Json_dispose(json);
    }
}

void MJsonDataManager::load() {
    const int files = 6;
    std::string names[files] = {"weapons", "enemies", "weaponLoaders", "bullets", "colonels", "majors"};
    
    for (int index = 0; index < files; index++) {
        char buff[50];
        sprintf(buff, "configuration/%s.json", names[index].c_str());
        Json* json = MJsonUtils::loadFileAsJson(buff);
        JSON_DOC[names[index]] = json;
    }
}