#include <list>
#include "AABBColider.h"

class CollisionManager {
    private:
        std::list<AABBCollider*> activeColliders;

    public:
        void UpdateActiveColliders();

        void UpdateCollider(AABBCollider* _col);

        void DrawColliders();

        void RegisterCollider(AABBCollider* _collider);

        bool CheckRectangleCollision(AABBCollider* _colA, AABBCollider* _colB);

        void SolveCollision(AABBCollider *_colA, AABBCollider *_colB);
        
};