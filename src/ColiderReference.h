#include "raylib.h"
#include "CollisionManager.h"

#include <memory>

class ColiderReference {
    public:
        ColiderReference(Vector2 _position, Vector2 _size, bool _isStatic);

        std::shared_ptr<AABBCollider> GetCollider();

    private:
    std::shared_ptr<AABBCollider> collider;
};