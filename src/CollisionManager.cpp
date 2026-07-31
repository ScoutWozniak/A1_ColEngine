#include "CollisionManager.h"

#include <bits/stdc++.h>
#include <math.h>

CollisionManager::CollisionManager()
{
    
}

void CollisionManager::InitialiseManager()
{
    g_Instance =  this;
}

std::shared_ptr<AABBCollider> CollisionManager::CreateCollider(Vector2 _position, Vector2 _size, bool _isStatic)
{

    AABBCollider newCollider = AABBCollider(_position, _size, _isStatic);
    m_registeredColliders.emplace_back(newCollider);

    std::shared_ptr<AABBCollider> storedPointer = std::make_shared<AABBCollider>(newCollider);
    m_colliderReferences.emplace_back(storedPointer);
    return storedPointer;
}


void CollisionManager::UpdateActiveColliders()
{
    for (std::shared_ptr<AABBCollider> collider : m_colliderReferences) {
        if (collider->GetIsStatic()) return;
        UpdateCollider(collider);
    }
}

void CollisionManager::UpdateCollider(std::shared_ptr<AABBCollider> _col)
{
    for (std::shared_ptr<AABBCollider> otherCollider : m_colliderReferences) {
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
    if (m_colliderReferences.empty())
        return;

    //TryDrawCollisionRec(activeColliders.front(), activeColliders.back());
    for (std::shared_ptr<AABBCollider> collider : m_colliderReferences) {
        if (!collider)
            return;
        collider->Draw();
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

void CollisionManager::SolveCollision(std::shared_ptr<AABBCollider> _colA, std::shared_ptr<AABBCollider> _colB) {
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

std::unique_ptr<CollisionManager> CollisionManager::GetInstance()
{
    std::unique_ptr<CollisionManager> instance(CollisionManager::g_Instance);
    return instance;
}

bool CollisionManager::CheckRectangleCollision(std::shared_ptr<AABBCollider> _colA, std::shared_ptr<AABBCollider> _colB)
{
    return CheckCollisionRecs(_colA->GetRectangle(), _colB->GetRectangle());
}
