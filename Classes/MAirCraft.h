//
//  MAirCraft.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MAirCraft_h
#define EarthWarrior3D_MAirCraft_h

#include "cocos2d.h"
#include "MGameEntity.h"
#include "json/document.h"

class MAirCraft : public MGameEntity {
public:
    virtual bool init();
    
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(int, _hp, HP);
    void initWithJson(const rapidjson::Document& document);
    void initWithJson(const char* fileName);
    void print();
};

#endif
