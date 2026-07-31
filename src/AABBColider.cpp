#include "AABBColider.h"

AABBCollider::AABBCollider()
{
    AABBCollider({0,0}, {32,32}, true);
}

AABBCollider::AABBCollider(Vector2 position, Vector2 size, bool _isStatic)
{
    recCollider.x = position.x;
    recCollider.y = position.y;
    recCollider.width = size.x;
    recCollider.height = size.y;


    debugDrawColor.r = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.g = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.b = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.a = 255;

    isStatic = _isStatic;
}


// TODO - remove this functionality from the collider and move it to a debug system we don't need it!
void AABBCollider::Draw()
{
    if (isStatic) {
        DrawRectangle(recCollider.x, recCollider.y, recCollider.width, recCollider.height, ColorAlpha(debugDrawColor, 0.5f));
    }
    DrawRectangleLinesEx(recCollider, 2.0f, debugDrawColor);
    DrawCircle(recCollider.x, recCollider.y, 8.0f, debugDrawColor);
}

void AABBCollider::SetPosition(Vector2 _position)
{  
    recCollider.x = _position.x;
    recCollider.y = _position.y;
}
