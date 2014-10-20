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
    std::string names[2] = {"weapons","enemies"};
    
    for (int index = 0; index < 2; index++) {
        char buff[20];
        sprintf(buff, "configuration/%s.json", names[index].c_str());
        rapidjson::Document doc;
        MJsonUtils::loadFileAsJson(buff, doc);
        JSON_DOC.AddMember(names[index].c_str(), doc["value"], JSON_DOC.GetAllocator());
    }
}