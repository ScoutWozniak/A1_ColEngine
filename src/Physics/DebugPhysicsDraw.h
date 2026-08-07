#pragma once

#include <string>
#include "CollisionManager.h"

void DrawPhysicsBody(PhysicsBody* _body) {
    _body->GetCollider()->Draw();

    std::string _velText = std::to_string(_body->m_velocity.x) + ", " + std::to_string(_body->m_velocity.y);
    std::string _velLength = std::to_string(Vector2Length(_body->m_velocity));
    DrawText(_velText.c_str(), _body->GetPosition().x, _body->GetPosition().y + 10, 10, _body->m_isAsleep ? RED : WHITE);
    DrawText(_velLength.c_str(), _body->GetPosition().x, _body->GetPosition().y + 30, 10, _body->m_isAsleep ? RED : WHITE);

}