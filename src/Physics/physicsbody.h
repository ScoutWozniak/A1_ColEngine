// -------------------
// Physics body is inherited by several other classes to extend functionality (i.e Kinematic, Static)
// It has no default behaviour other than initialising a collider
// --------------------

#pragma once


#include "AABBColider.h"
#include "raylib.h"

class PhysicsBody {
    public:
    
        PhysicsBody() { PhysicsBody(Rectangle{0,0,32,32}, true); }
        PhysicsBody(Rectangle _collider, bool _isStatic);

        ~PhysicsBody();

        AABBCollider GetCollider();

        bool m_isStatic = false;
    private:
        AABBCollider m_collider;
};