#include "AABBColider.h"

AABBCollider::AABBCollider()
{
    AABBCollider({0,0}, {32,32}, true);
}

AABBCollider::AABBCollider(Vector2 position, Vector2 size, bool _isStatic)
{
    m_collider = {{position.x, position.y, size.x, size.y}, _isStatic};


    debugDrawColor.r = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.g = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.b = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.a = 255;
}


// TODO - remove this functionality from the collider and move it to a debug system we don't need it!
void AABBCollider::Draw()
{
    if (m_collider.m_isStatic) {
        DrawRectangle(m_collider.m_size.x, m_collider.m_size.y, m_collider.m_size.width, m_collider.m_size.height, ColorAlpha(debugDrawColor, 0.5f));
    }
    DrawRectangleLinesEx(m_collider.m_size, 2.0f, debugDrawColor);
    DrawCircle(m_collider.m_size.x, m_collider.m_size.y, 8.0f, debugDrawColor);
}

void AABBCollider::SetPosition(Vector2 _position)
{  
    m_collider.m_size.x = _position.x;
    m_collider.m_size.y = _position.y;
}
