//
//  MGameScene.h
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#ifndef EarthWarrior3D_MGameScene_h
#define EarthWarrior3D_MGameScene_h

#include "cocos2d.h"
#include "MEnemyGeneral.h"
/**
scene's layer
    background_layer
    game_layer
    effect_layer
    ui_layer
    foreground_layer
 
game_layer's layer
    enemy_layer
    player_layer
    bullet_layer

 bullet_layer's layer:
    player_bullets_layer
    batch_bullets_layer
    enemy_bullets_layer
 
 batch_bullets_layer
    player_batched_bullets
    enemy_batched_bullets
*/

enum SceneZOrder {
    bg_layer,
    game_layer,
    effect_layer,
    fg_layer,
    ui_layer
};

enum GameZOrder {
    enemy_layer,
    player_layer,
    bullet_layer
};

enum BulletZOrder {
    player,
    batched,
    enemy
};

enum BatchedBulletZOrder {
    player_batched,
    enemy_batched
};

class MWeapon2;

class MGameScene : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MGameScene);
    
    virtual bool init();
    virtual void update(float dt);
    virtual void onEnter();
    
    MGameScene() : _xScroll(0.0f){};
private:
    void initLayer();
    void initBackground();
    void updateBackground(float dt);
    void addLayerByZOrder(int zorder);
    
private:
    cocos2d::Sprite* _background;
    float _xScroll;
    MEnemyGeneral* general;
};


#endif
