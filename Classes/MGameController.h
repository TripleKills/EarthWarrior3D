//
//  MGameController.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-9-2.
//
//

#ifndef EarthWarrior3D_MGameController_h
#define EarthWarrior3D_MGameController_h

#include "cocos2d.h"
#include "MGameEntity.h"

class MGameController {
public:
    static MGameController* getInstance() {
        if (nullptr == _sInstance) {
            _sInstance = new MGameController();
        }
        return _sInstance;
    }
    
    CC_SYNTHESIZE(MGameEntity*, _player, Player);
    
    MGameEntity* getRandomEnemy() {return _aliveEnemys.getRandomObject();};
    
public:
    static cocos2d::Vector<MGameEntity*> _aliveEnemys;
private:
    static MGameController* _sInstance;
    MGameController(){ _player = nullptr; };
};

#endif
