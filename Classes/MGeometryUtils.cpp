//
//  MGeometryUtils.cpp
//  EarthWarrior3D
//
//  Created by qinyuanz on 14-8-20.
//
//

#include "MGeometryUtils.h"

USING_NS_CC;

void MGeometryUtils::aim(Node* node, Node* target) {
    Vec2 delta = target->getPosition() - node->getPosition();
    float angleRad = delta.getAngle();
    float angleDeg = CC_RADIANS_TO_DEGREES(angleRad);
    if (node->getRotation() != 90 - angleDeg) {
        node->setRotation(90 - angleDeg);
    }
}