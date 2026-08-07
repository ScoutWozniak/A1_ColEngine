// -------------------
// Physics body is inherited by several other classes to extend functionality (i.e Kinematic, Static)
// It has no default behaviour other than initialising a collider
// --------------------

#pragma once


#include "AABBColider.h"
#include "raylib.h"
#include "raymath.h"
#include "PhysicsProperties.h"

enum AwakeStages {
    AWAKE = 0,
    AWAITING_SLEEP = 1,
    ASLEEP = 2
};


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

        Vector2 GetDeltaVelocity() {
            return Vector2Multiply(m_velocity, Vector2{GetFrameTime(), GetFrameTime()});
        }

        AABB GetBroadPhaseCollider();

        void UpdateForces();

        bool m_usesGravity = true;

        PhysicsProperties m_physicsProperties = {1.0f, 0.1f};

        bool m_isAsleep = false;

        void UpdateSleep();

        void TryAwake() {m_awakeStage = AWAKE;}

        bool GetIsAsleep() {return m_awakeStage == ASLEEP; }
    private:
        AABBCollider m_collider;

        AwakeStages m_awakeStage =  AWAKE;
        float m_noVelStart = 0.0f;

        const float ASLEEP_THRESHOLD = 1.0f;
        const float ASLEEP_DELAY = 0.5f;
};