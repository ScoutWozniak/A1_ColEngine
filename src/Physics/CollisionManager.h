#include <list>
#include "AABBColider.h"

// We should only need to reference the base physics class, all logic should replace virtual methods if need be
#include "Physics/physicsbody.h"


#define NARROW_STAGE_ITERRATIONS 3

class CollisionManager {
    private:
        std::list<AABBCollider*> activeColliders;

        std::list<PhysicsBody> physicsBodies; 

        std::list<PhysicsBody*> physicsPointers;
        

    public:
        // Physics body related code

        template<typename T>
        T* CreatePhysicsBody(AABB _aabb);

        void DrawColliders();

        void RegisterCollider(AABBCollider* _collider);

        bool CheckRectangleCollision(AABBCollider* _colA, AABBCollider* _colB);

        bool BroadStage(PhysicsBody *_col, PhysicsBody *_colB);

        bool NarrowStage(PhysicsBody *_colA, PhysicsBody *_colB);

        void NarrowStage(std::list<PhysicsBody *> _narrowBodies, PhysicsBody *_mainCol);

        void SolveCollision(PhysicsBody *_colA, PhysicsBody *_colB);
        
        void UpdatePhysicsWorld();

        void UpdatePhysicsBody(PhysicsBody *_physicsBody);

        int GetBodyCount() {return physicsBodies.size(); }
};

template<typename T>
inline T * CollisionManager::CreatePhysicsBody(AABB _aabb)
{
    PhysicsBody newBody = PhysicsBody{_aabb};

    PhysicsBody* bodyReference = &physicsBodies.emplace_back(newBody);

    physicsPointers.emplace_back(bodyReference);

    return bodyReference;
}