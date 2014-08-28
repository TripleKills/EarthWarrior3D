//
//  MStringUtils.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MStringUtils_h
#define EarthWarrior3D_MStringUtils_h

#include "cocos2d.h"

class MStringUtils {
public:
    static std::string removeDirAndReplacePostfix(const char* plist, const char* newPostfix);
    
    static std::string &ltrim(std::string &s);
    
    // trim from end
    static std::string &rtrim(std::string &s);
    
    // trim from both ends
    static std::string &trim(std::string &s);
    
    static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    
    static std::vector<std::string> split(const std::string &s, char delim);
    
    static float toFloat( std::string myString );
    
    static cocos2d::Vec3 parseVec3(const std::string &myString);
    
    static cocos2d::Vec2 parseVec2(const std::string &myString);
};

#endif
