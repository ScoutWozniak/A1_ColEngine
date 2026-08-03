#include <list>
#include "AABBColider.h"

// We should only need to reference the base physics class, all logic should replace virtual methods if need be
#include "Physics/physicsbody.h"


class CollisionManager {
    private:
        std::list<AABBCollider*> activeColliders;

        std::list<PhysicsBody> physicsBodies; 
        

    public:
        // Physics body related code

        template<typename T>
        T* CreatePhysicsBody(AABB _aabb);

        void UpdateActiveColliders();

        void UpdateCollider(AABBCollider* _col);

        void DrawColliders();

        void RegisterCollider(AABBCollider* _collider);

        bool CheckRectangleCollision(AABBCollider* _colA, AABBCollider* _colB);

        void SolveCollision(AABBCollider *_colA, AABBCollider *_colB);
        
};

template<typename T>
inline T * CollisionManager::CreatePhysicsBody(AABB _aabb)
{
    PhysicsBody newBody = PhysicsBody{_aabb};

    

    return &physicsBodies.emplace_back(newBody);
}