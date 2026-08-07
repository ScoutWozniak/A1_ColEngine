#pragma once

#include <string>
#include "Physics/CollisionManager.h"

#ifndef DEBUGPHYSDRAW_H
#define DEBUGPHYSDRAW_H

namespace DebugDraw {
    void DrawPhysicsBody(PhysicsBody* _body);

    void DrawHighlight(PhysicsBody* _body);

    void DrawDebugMenu(PhysicsBody* _body);

    const float DEBUG_MENU_WIDTH = 300;
    const float DEBUG_MENU_HEIGHT = 200;
}



#endif