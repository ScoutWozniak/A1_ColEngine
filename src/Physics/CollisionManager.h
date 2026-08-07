#pragma once

#include <list>
#include "AABBColider.h"

// We should only need to reference the base physics class, all logic should replace virtual methods if need be
#include "Physics/physicsbody.h"


#define NARROW_STAGE_ITERRATIONS 3

class CollisionManager {
    private:
        std::list<PhysicsBody> m_physicsBodies; 

        std::list<PhysicsBody*> m_physicsPointers;
        

    public:

        bool m_pausePhysics = false;

        template<typename T>
        T* CreatePhysicsBody(AABB _aabb);

        void DrawColliders();

        bool CheckRectangleCollision(AABBCollider* _colA, AABBCollider* _colB);

        bool BroadStage(PhysicsBody *_col, PhysicsBody *_colB);

        bool NarrowStage(PhysicsBody *_colA, PhysicsBody *_colB);

        void NarrowStage(std::list<PhysicsBody *> _narrowBodies, PhysicsBody *_mainCol);

        void SolveCollision(PhysicsBody *_colA, PhysicsBody *_colB);
        
        void UpdatePhysicsWorld();

        void UpdatePhysicsBody(PhysicsBody *_physicsBody);

        int GetBodyCount() {return m_physicsBodies.size(); }

        Vector2 CalculateCollisionVelocity(Vector2 _bodyVelocity, Vector2 _collisionNormal);

        Vector2 CancelCollisionNormal(Vector2 _bodyVelocity, Vector2 _collisionNormal);

        ~CollisionManager() {
            for (PhysicsBody* _body : m_physicsPointers) {
                delete _body;
            }
        }

        
};

template<typename T>
inline T * CollisionManager::CreatePhysicsBody(AABB _aabb)
{
    PhysicsBody newBody = PhysicsBody{_aabb};

    PhysicsBody* bodyReference = &m_physicsBodies.emplace_back(newBody);

    m_physicsPointers.emplace_back(bodyReference);

    return bodyReference;
}