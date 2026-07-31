#include "physicsbody.h"

PhysicsBody::PhysicsBody(Rectangle _collider, bool _isStatic)
{
    m_collider = AABBCollider{{_collider.x,_collider.y}, {_collider.width,_collider.height}, false};

    // TODO - Hook into physics manager here
}

PhysicsBody::~PhysicsBody()
{
    // Remove references here
}

AABBCollider PhysicsBody::GetCollider()
{
    return m_collider;
}
