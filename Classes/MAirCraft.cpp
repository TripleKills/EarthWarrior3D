//
//  MAirCraft.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MAirCraft.h"

bool MAirCraft::init() {
    if(!MGameEntity::init()) {
        return false;
    }
    return true;
}