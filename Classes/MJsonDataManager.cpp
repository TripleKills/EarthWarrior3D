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
    //std::string names[files] = {"weapons", "enemies", "weaponLoaders", "bullets"};
    /**
    for (int index = 0; index < files; index++) {
        char buff[50];
        sprintf(buff, "configuration/%s.json", names[index].c_str());
        rapidjson::Document doc;
        MJsonUtils::loadFileAsJson(buff, doc);
        JSON_DOC.AddMember(names[index].c_str(), doc["value"], JSON_DOC.GetAllocator());
    }
     */
    rapidjson::Document doc;
    MJsonUtils::loadFileAsJson("configuration/weapons.json", doc);
    JSON_DOC.AddMember("weapons", doc["value"], JSON_DOC.GetAllocator());
    MJsonUtils::loadFileAsJson("configuration/enemies.json", doc);
    JSON_DOC.AddMember("enemies", doc["value"], JSON_DOC.GetAllocator());
    MJsonUtils::loadFileAsJson("configuration/weaponLoaders.json", doc);
    JSON_DOC.AddMember("weaponLoaders", doc["value"], JSON_DOC.GetAllocator());
    MJsonUtils::loadFileAsJson("configuration/bullets.json", doc);
    JSON_DOC.AddMember("bullets", doc["value"], JSON_DOC.GetAllocator());
}