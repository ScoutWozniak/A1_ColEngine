#include "CollisionManager.h"
#include <bits/stdc++.h>
#include <math.h>
#include "raymath.h"


void TryDrawCollisionRec(AABBCollider* _colA, AABBCollider* _colB) {
    if (CheckCollisionRecs(_colA->GetRectangle(), _colB->GetRectangle())) {
        Rectangle colRec = GetCollisionRec(_colA->GetRectangle(), _colB->GetRectangle());
        DrawRectanglePro(colRec, {0,0}, 0.0f, RED);


        // Debuging size of collision
        std::string debugSize = std::to_string(colRec.width) + ", " + std::to_string(colRec.height);
        DrawText(debugSize.c_str(), 0, 30, 15, BLUE);
    }
}

void CollisionManager::DrawColliders()
{
    //TryDrawCollisionRec(activeColliders.front(), activeColliders.back());
    for (PhysicsBody body : physicsBodies) {
        AABBCollider* col = body.GetCollider();
        col->Draw();
        
    }
}

void CollisionManager::RegisterCollider(AABBCollider *_collider)
{
    activeColliders.emplace_back(_collider);
}

enum SolveDirections {
    AXIS_WIDTH,
    AXIS_HEIGHT
};

void CollisionManager::SolveCollision(PhysicsBody *_colA, PhysicsBody *_colB) {
    AABBCollider* _colliderA = _colA->GetCollider();
    AABBCollider* _colliderB = _colB->GetCollider();

    Rectangle collisionRect = GetCollisionRec(_colliderA->GetRectangle(), _colliderB->GetRectangle());

    bool bothActive = !_colliderA->GetIsStatic() && !_colliderB->GetIsStatic();

    SolveDirections solveDirection = AXIS_WIDTH;
    if (abs((long)collisionRect.height) < abs((long)collisionRect.width)) { solveDirection = AXIS_HEIGHT; }

    float aPos = solveDirection == AXIS_WIDTH ? _colliderA->GetRectangle().x : _colliderA->GetRectangle().y;
    float bPos = solveDirection == AXIS_WIDTH ? collisionRect.x : collisionRect.y;

    float solveDir = aPos < bPos ? -1.0f : 1.0f;
    Vector2 newPosition = {_colliderA->GetRectangle().x, _colliderA->GetRectangle().y };

    Vector2 solutionDirection = {solveDirection == AXIS_WIDTH ? solveDir : 0.0f, solveDirection == AXIS_HEIGHT ? solveDir : 0.0f};
    if (solveDirection == AXIS_WIDTH) newPosition.x += solveDir * collisionRect.width;
    else newPosition.y += solveDir * collisionRect.height;
    _colA->SetPositon(newPosition);
    // Stop velocity on the collision axis
    _colA->m_velocity = (_colA->m_velocity, (_colA->m_velocity, solutionDirection));
}

void CollisionManager::UpdatePhysicsWorld()
{
    for (PhysicsBody* body : physicsPointers) {
        if (!body->m_isStatic) {UpdatePhysicsBody(body);}
    }
}

void CollisionManager::UpdatePhysicsBody(PhysicsBody* _physicsBody) {

    _physicsBody->UpdateForces();

    std::list<PhysicsBody*> broadStageCollisions;
    for (PhysicsBody* otherBody : physicsPointers) {
        if (otherBody == _physicsBody) continue;

        if (BroadStage(_physicsBody, otherBody)) {
            // Batch all potentially overlapping colliders so we can calculate things accurately
            broadStageCollisions.emplace_back(otherBody);
        }
    }

    NarrowStage(broadStageCollisions, _physicsBody);
}

bool CollisionManager::CheckRectangleCollision(AABBCollider *_colA, AABBCollider *_colB)
{
    return CheckCollisionRecs(_colA->GetRectangle(), _colB->GetRectangle());
}

// Check overlap of bodies accounting for velocity
bool CollisionManager::BroadStage(PhysicsBody* _col, PhysicsBody* _colB) {
    return CheckCollisionRecs(_col->GetBroadPhaseCollider().m_size, _colB->GetCollider()->GetRectangle());
}


// NOTE: This stage features a lot of iteration and is far too slow
// TODO: Further optimisations
void CollisionManager::NarrowStage(std::list<PhysicsBody*> _narrowBodies, PhysicsBody* _mainCol) {
    Vector2 currentSize = {_mainCol->GetCollider()->GetRectangle().width, _mainCol->GetCollider()->GetRectangle().height};

    bool collisionOnIteration = false;

    std::list<PhysicsBody*> _narrowColliders;

    int collidingIteration = -1;
    for (int i = 0; i <= NARROW_STAGE_ITERRATIONS; i++) {


        Vector2 velocityStage = (_mainCol->GetDeltaVelocity() * (i / NARROW_STAGE_ITERRATIONS));
        Vector2 currentStagePosition = Vector2Add( _mainCol->GetPosition(), velocityStage);
        AABB currentStageCollider = {{currentStagePosition.x, currentStagePosition.y,currentSize.x, currentSize.y}, false};

        for (PhysicsBody* _collider : _narrowBodies) {
            bool narrowCol = CheckCollisionRecs(currentStageCollider.m_size, _collider->GetCollider()->GetRectangle());

            if (narrowCol) {
                collisionOnIteration = true;
                collidingIteration = i;

                _narrowColliders.emplace_back(_collider);
            }
        }

        if (collisionOnIteration) {
            _mainCol->SetPositon(currentStagePosition);
        }
    }

    if (!collisionOnIteration) {
        _mainCol->SetPositon(Vector2Add(_mainCol->GetPosition(), _mainCol->GetDeltaVelocity() ) );
        return;
    }

    for (PhysicsBody* finalCollisions : _narrowColliders) {
        SolveCollision(_mainCol, finalCollisions);
    }
}


