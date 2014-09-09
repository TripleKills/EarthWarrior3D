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

std::string &MStringUtils::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &MStringUtils::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &MStringUtils::trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::vector<std::string> &MStringUtils::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> MStringUtils::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

//isFloat taken from http://stackoverflow.com/questions/447206/c-isfloat-function
float MStringUtils::toFloat( std::string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    if( iss.eof() && !iss.fail() ) {
        return f;
    } else {
        return 0.0f;
    }
}

Vec3 MStringUtils::parseVec3(const std::string &myString) {
    std::vector<std::string> vec = MStringUtils::split(myString, ',');
    return Vec3(MStringUtils::toFloat(vec.at(0)),
                        MStringUtils::toFloat(vec.at(1)),
                        MStringUtils::toFloat(vec.at(2)));
}

Vec2 MStringUtils::parseVec2(const std::string &myString) {
    std::vector<std::string> vec = MStringUtils::split(myString, ',');
    return Vec2(MStringUtils::toFloat(vec.at(0)),
                MStringUtils::toFloat(vec.at(1)));
}

Rect MStringUtils::parseRect(const std::string &myString) {
    std::vector<std::string> vec = MStringUtils::split(myString, ',');
    return Rect(MStringUtils::toFloat(vec.at(0)),
                MStringUtils::toFloat(vec.at(1)),
                MStringUtils::toFloat(vec.at(2)),
                MStringUtils::toFloat(vec.at(3)));
}