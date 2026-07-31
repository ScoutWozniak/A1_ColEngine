#include "ColiderReference.h"


ColiderReference::ColiderReference(Vector2 _position, Vector2 _size, bool _isStatic)
{
    std::shared_ptr<CollisionManager> colManager = CollisionManager::GetInstance();

    collider = colManager->CreateCollider(_position, _size, _isStatic);
}