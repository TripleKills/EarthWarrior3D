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
#include "MMacros.h"

class MAirCraft : public MGameEntity {
public:
    virtual void initWithJson(const rapidjson::Value& document);
    virtual void print();
    
    bool hurt(int damage, cocos2d::Vec2 position = nullptr);
    
    CC_SYNTHESIZE_READONLY(int, _MAX_HP, MaxHP);
    CC_SYNTHESIZE(int, _hp, HP);

protected:
    MAirCraft(){};
    virtual void onHurt(int damage, cocos2d::Vec2 position);
    virtual void onDead();
};

#endif
