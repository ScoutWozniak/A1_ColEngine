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
    Vector2 nextWidth = Vector2Add({m_collider.GetRectangle().width, m_collider.GetRectangle().height }, m_velocity );
    return AABB(Rectangle{GetPosition().x, GetPosition().y, nextWidth.x, nextWidth.y}, false);
}
