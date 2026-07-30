#include "AABBColider.h"

AABBCollider::AABBCollider(Vector2 size, Vector2 position)
{
    recCollider.x = position.x;
    recCollider.y = position.y;
    recCollider.width = size.x;
    recCollider.height = size.y;


    debugDrawColor.r = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.g = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.b = (unsigned char)GetRandomValue(0,255);
    debugDrawColor.a = 255;
}

void AABBCollider::Draw()
{
    DrawRectangleLinesEx(recCollider, 2.0f, debugDrawColor);
}
