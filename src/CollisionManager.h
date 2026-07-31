#include <list>
#include "AABBColider.h"

#include <memory>

class CollisionManager {
    private:
        std::list<AABBCollider*> activeColliders;

        std::list<std::shared_ptr<AABBCollider>> m_registeredColliders;

    public:

        inline static CollisionManager * g_Instance;

        CollisionManager();

        void InitialiseManager();

        std::shared_ptr<AABBCollider> CreateCollider(Vector2 _position, Vector2 _size, bool _isStatic);

        void UpdateActiveColliders();

        void UpdateCollider(AABBCollider* _col);

        void DrawColliders();

        void RegisterCollider(AABBCollider* _collider);

        bool CheckRectangleCollision(AABBCollider* _colA, AABBCollider* _colB);

        void SolveCollision(AABBCollider *_colA, AABBCollider *_colB);

        static std::unique_ptr<CollisionManager> GetInstance();
        
};