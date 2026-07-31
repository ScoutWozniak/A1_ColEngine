// -------------------
// Physics body is inherited by several other classes to extend functionality (i.e Kinematic, Static)
// It has no default behaviour other than initialising a collider
// --------------------

#pragma once


#include "AABBColider.h"
#include "raylib.h"

class PhysicsBody {
    public:
        PhysicsBody(Rectangle _collider);
        ~PhysicsBody();

        AABBCollider GetCollider();
    private:
        AABBCollider m_collider;
};