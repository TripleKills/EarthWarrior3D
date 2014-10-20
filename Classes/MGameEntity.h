//
//  MGameEntity.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MGameEntity_h
#define EarthWarrior3D_MGameEntity_h

#include "cocos2d.h"
#include "MMacros.h"


class MGameEntity : public cocos2d::Node {
public:
    virtual void initWithJson(const rapidjson::Value& document);
    virtual void print();
    
    void forward(float dist);
    void forward(float dist, float angle);

    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE_READONLY(float, _radius, Radius);
    CC_SYNTHESIZE_READONLY(cocos2d::Vec3, _orientation, Orientation);
    CC_SYNTHESIZE(float, _speed, Speed);
protected:
    MGameEntity(){};
    cocos2d::Node* _model;
};



#endif
