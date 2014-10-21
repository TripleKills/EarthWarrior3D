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

enum EntityFaces {
    DOWN,
    UP
};

class MGameEntity : public cocos2d::Node {
public:
    virtual void initWithJson(Json* document);
    virtual void print();
    
    void forward(float dist);
    void forward(float dist, float angle);
    void rotate(float angle);
    void addChildEntity(MGameEntity* child);
    
    virtual void setFace(EntityFaces face);
    EntityFaces getFace() {return _face;};

    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE_READONLY(float, _radius, Radius);
    CC_SYNTHESIZE_READONLY(cocos2d::Vec3, _orientation, Orientation);
    CC_SYNTHESIZE(float, _speed, Speed);
protected:
    EntityFaces _face;
    MGameEntity(): _type(kNone), _face(DOWN), _speed(0.0f), _radius(0.0f){};
    cocos2d::Node* _model;
};



#endif
