#include <list>
#include "AABBColider.h"

#include <memory>

class CollisionManager {
    private:
        std::list<AABBCollider*> activeColliders;

        std::list<std::shared_ptr<AABBCollider>> m_colliderReferences;


        std::list<AABBCollider> m_registeredColliders;
    public:

        inline static CollisionManager * g_Instance;

        CollisionManager();

        void InitialiseManager();

        std::shared_ptr<AABBCollider> CreateCollider(Vector2 _position, Vector2 _size, bool _isStatic);

        void UpdateActiveColliders();

        void UpdateCollider(std::shared_ptr<AABBCollider> _col);

        void DrawColliders();

        void RegisterCollider(AABBCollider* _collider);

        bool CheckRectangleCollision(std::shared_ptr<AABBCollider> _colA, std::shared_ptr<AABBCollider> _colB);

        void SolveCollision(std::shared_ptr<AABBCollider> _colA, std::shared_ptr<AABBCollider> _colB);

        static std::unique_ptr<CollisionManager> GetInstance();
        
};