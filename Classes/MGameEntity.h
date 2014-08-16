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
#include "MConsts.h"

class MGameEntity : public cocos2d::Node {
public:
    CREATE_FUNC(MGameEntity);
    
    MGameEntity(): _type(entityTypes::kNone), _radius(0.0f), _orientation(cocos2d::Vec3(0,0,0)){};
    
    virtual bool init();
    void forward(float dist);
    void forward(float dist, float angle);

    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE_READONLY(float, _radius, Radius);
    CC_SYNTHESIZE_READONLY(cocos2d::Vec3, _orientation, Orientation);
protected:
    cocos2d::Node* _model;
};

#endif
