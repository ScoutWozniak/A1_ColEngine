#include "physicsbody.h"
#include "raymath.h"

PhysicsBody::PhysicsBody(Rectangle _collider, bool _isStatic)
{
    m_collider = AABBCollider{{_collider.x,_collider.y}, {_collider.width,_collider.height}, false};

    // TODO - Hook into physics manager here
}

PhysicsBody::PhysicsBody(AABB _aabb)
{
    m_collider = AABBCollider{_aabb};
    m_isStatic = m_collider.GetIsStatic();
}

PhysicsBody::~PhysicsBody()
{
    // Remove references here
}

AABBCollider* PhysicsBody::GetCollider()
{
    return &m_collider;
}

AABB PhysicsBody::GetBroadPhaseCollider()
{
    Vector2 nextWidth = Vector2Add({m_collider.GetRectangle().width, m_collider.GetRectangle().height }, GetDeltaVelocity() );
    return AABB(Rectangle{GetPosition().x, GetPosition().y, nextWidth.x, nextWidth.y}, false);
}

void PhysicsBody::UpdateForces()
{
    if (m_usesGravity) {
        m_velocity.y += 9.8f;
    }
}

void PhysicsBody::UpdateSleep()
{
    bool metThreshold = abs( Vector2Length(m_velocity) <= ASLEEP_THRESHOLD);

    if (!metThreshold) {
        m_awakeStage = AWAKE;
        return;
    }

    switch(m_awakeStage) {
        case AWAKE:
            m_noVelStart = GetTime();
            m_awakeStage = AWAITING_SLEEP;
            return;
        case AWAITING_SLEEP:
            if (m_noVelStart + ASLEEP_DELAY <= GetTime()) {
                m_awakeStage = ASLEEP;
            }
            return;
        case ASLEEP:
            return;

    }


}
