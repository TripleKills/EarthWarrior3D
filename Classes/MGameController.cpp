//
//  MGameController.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-9-2.
//
//

#include "MGameController.h"

USING_NS_CC;

MGameController* MGameController::_sInstance = nullptr;

Vector<MGameEntity*> MGameController::_aliveEnemys;
