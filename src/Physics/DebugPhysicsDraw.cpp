#include "Physics/DebugPhysicsDraw.h"
#include "DebugPhysicsDraw.h"

void DebugDraw::DrawPhysicsBody(PhysicsBody* _body) {
        _body->GetCollider()->Draw();

        std::string _velText = std::to_string(_body->m_velocity.x) + ", " + std::to_string(_body->m_velocity.y);
        std::string _velLength = std::to_string(Vector2Length(_body->m_velocity));
        DrawText(_velText.c_str(), _body->GetPosition().x, _body->GetPosition().y + 10, 10, _body->m_isAsleep ? RED : WHITE);
        DrawText(_velLength.c_str(), _body->GetPosition().x, _body->GetPosition().y + 30, 10, _body->m_isAsleep ? RED : WHITE);
    }

void DebugDraw::DrawHighlight(PhysicsBody* _body) {
    Rectangle rect = _body->GetCollider()->GetRectangle();
    DrawRectanglePro(rect, Vector2Zero(), 0.0f, ColorLerp(BLUE, WHITE, sin(GetTime())));
}

void DebugDraw::DrawDebugMenu(PhysicsBody *_body)
{
    Vector2 debugPosition = {GetScreenWidth() - DEBUG_MENU_WIDTH, 0};
    DrawRectangle(debugPosition.x, debugPosition.y, DEBUG_MENU_WIDTH, DEBUG_MENU_HEIGHT, GRAY);

    std::string _static = "Is Static: " + std::to_string(_body->m_isStatic);
    std::string _sleep = "Is Asleep: " + std::to_string(_body->m_isAsleep);
    std::string _buffer = "------------";
    std::string _position = "Pos: " + std::to_string(_body->GetPosition().x) + ", " + std::to_string(_body->GetPosition().y);
    std::string _velText = "Velocity: " + std::to_string(_body->m_velocity.x) + ", " + std::to_string(_body->m_velocity.y);
    std::string _velLength = "Length: " + std::to_string(Vector2Length(_body->m_velocity));

    std::list<std::string> debugStrings = {_static, _sleep, _buffer, _position, _velText, _velLength};

    int vertOffset = 0;
    for (std::string str : debugStrings) {
        DrawText(str.c_str(), debugPosition.x + 10, debugPosition.y + vertOffset, 20, WHITE);

        vertOffset += 20;
    }
    

}