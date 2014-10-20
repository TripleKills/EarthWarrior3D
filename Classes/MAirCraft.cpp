//
//  MAirCraft.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MAirCraft.h"
#include "MJsonUtils.h"
#include <vector>
#include "MStringUtils.h"

USING_NS_CC;

void MAirCraft::initWithJson(Json* document) {
    MGameEntity::initWithJson(document);
    
    _MAX_HP = Json_getInt(document, "hp", 0);
    _hp = _MAX_HP;
}

void MAirCraft::print() {
    MGameEntity::print();
    CCLOG("MAirCraft:[hp/maxhp:%d/%d]", _hp, _MAX_HP);
}

bool MAirCraft::hurt(int damage, Vec2 position) {
    if (_hp <= 0) {
        CCLOG("MAirCraft: hp has been to %d, not big than 0, do not hurt", _hp);
        return false;
    }
    _hp -= damage;
    _hp = _hp >= 0 ? _hp : 0;
    position = position == nullptr ? getPosition() : position;
    onHurt(damage, position);
    if (_hp == 0) {
        onDead();
    }
    return true;
}

void MAirCraft::onHurt(int damage, cocos2d::Vec2 position) {
}
void MAirCraft::onDead() {
}