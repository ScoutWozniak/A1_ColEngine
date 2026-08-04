#include "CollisionManager.h"
#include <bits/stdc++.h>
#include <math.h>
#include "raymath.h"

void CollisionManager::UpdateActiveColliders()
{
    for (AABBCollider* collider : activeColliders) {
        if (collider->GetIsStatic()) return;
        UpdateCollider(collider);
    }
}



void CollisionManager::UpdateCollider(AABBCollider *_col)
{
    for (AABBCollider* otherCollider : activeColliders) {
        if (otherCollider == _col) continue;
        if (CheckRectangleCollision(_col, otherCollider)) {
            SolveCollision(_col, otherCollider);
        }
    }
}

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

void CollisionManager::SolveCollision(AABBCollider *_colA, AABBCollider *_colB) {
    Rectangle collisionRect = GetCollisionRec(_colA->GetRectangle(), _colB->GetRectangle());

    bool bothActive = !_colA->GetIsStatic() && !_colB->GetIsStatic();

    SolveDirections solveDirection = AXIS_WIDTH;
    if (abs((long)collisionRect.height) < abs((long)collisionRect.width)) { solveDirection = AXIS_HEIGHT; }

    float aPos = solveDirection == AXIS_WIDTH ? _colA->GetRectangle().x : _colA->GetRectangle().y;
    float bPos = solveDirection == AXIS_WIDTH ? collisionRect.x : collisionRect.y;

    float solveDir = aPos < bPos ? -1.0f : 1.0f;
    Vector2 newPosition = {_colA->GetRectangle().x, _colA->GetRectangle().y };
    if (solveDirection == AXIS_WIDTH) newPosition.x += solveDir * collisionRect.width;
    else newPosition.y += solveDir * collisionRect.height;
    _colA->SetPosition(newPosition);
}

void CollisionManager::UpdatePhysicsWorld()
{
    for (PhysicsBody* body : physicsPointers) {
        if (body->m_isStatic) continue;
        UpdatePhysicsBody(body);
    }
}

void CollisionManager::UpdatePhysicsBody(PhysicsBody* _physicsBody) {
    for (PhysicsBody* otherBody : physicsPointers) {
        if (otherBody == _physicsBody) continue;

        if (BroadStage(_physicsBody, otherBody)) {
            NarrowStage(_physicsBody, otherBody);
        }
    }
}

bool CollisionManager::CheckRectangleCollision(AABBCollider *_colA, AABBCollider *_colB)
{
    return CheckCollisionRecs(_colA->GetRectangle(), _colB->GetRectangle());
}

// Check overlap of bodies accounting for velocity
bool CollisionManager::BroadStage(PhysicsBody* _col, PhysicsBody* _colB) {
    return CheckRectangleCollision(_col->GetCollider(), _colB->GetCollider());
}

// Check overlap of bodies and then solve collision
bool CollisionManager::NarrowStage(PhysicsBody* _colA, PhysicsBody* _colB) {
    SolveCollision(_colA->GetCollider(), _colB->GetCollider());
    return true;
}


