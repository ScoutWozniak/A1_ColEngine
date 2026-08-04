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
        PhysicsBody(AABB _aabb);

        ~PhysicsBody();

        AABBCollider* GetCollider();

        bool m_isStatic = false;

        Vector2 GetPosition() {return {m_collider.GetRectangle().x, m_collider.GetRectangle().y};}

        void SetPositon(Vector2 _newPos) {m_collider.SetPosition(_newPos);}

        Vector2 m_velocity = {0,0};

        AABB GetBroadPhaseCollider();
        
    private:
        AABBCollider m_collider;
};