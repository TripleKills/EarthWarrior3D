//
//  MLayerUtil.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-16.
//
//

#include "MLayerUtil.h"
#include "MConsts.h"

USING_NS_CC;

void MLayerUtil::addLayerSameZorderTag(Node* node, int zorder) {
    auto layer = Layer::create();
    node->addChild(layer, zorder, zorder);
}

void MLayerUtil::addLayerSameZorderTag(int first, int last, cocos2d::Node* node) {
    for(int i = first; i <= last; i++) {
        MLayerUtil::addLayerSameZorderTag(node, i);
    }
}