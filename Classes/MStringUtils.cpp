//
//  MStringUtils.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MStringUtils.h"

USING_NS_CC;

std::string MStringUtils::removeDirAndReplacePostfix(const char* plist, const char* newPostfix) {
    if (plist == nullptr or newPostfix == nullptr) {
        return plist;
    }
    std::string str = plist;
    // remove dir
    size_t pos1 = str.find_last_of("/");
    if (pos1 != std::string::npos) {
        str = str.erase(0, pos1 + 1);
    }
    // remove .xxx
    size_t startPos = str.find_last_of(".");
    if (startPos != std::string::npos) {
        str = str.erase(startPos);
    }
    // append .png
    str = str.append(newPostfix);
    return str;
}