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

void MJsonDataManager::load() {
    const int files = 4;
    std::string names[files] = {"weapons", "enemies", "weaponLoaders", "bullets"};
    
    for (int index = 0; index < files; index++) {
        char buff[50];
        sprintf(buff, "configuration/%s.json", names[index].c_str());
        Json* json = MJsonUtils::loadFileAsJson(buff);
        JSON_DOC[names[index]] = json;
    }
}