#include "physicsbody.h"

PhysicsBody::PhysicsBody(Rectangle _collider)
{
    m_collider = AABBCollider{{_collider.x,_collider.y}, {_collider.width,_collider.height}, false};

    // TODO - Hook into physics manager here
}

PhysicsBody::~PhysicsBody()
{

}

AABBCollider PhysicsBody::GetCollider()
{
    return m_collider;
}
