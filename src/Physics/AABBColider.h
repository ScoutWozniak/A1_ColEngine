#pragma once

#include "raylib.h"

struct AABB {
    Rectangle m_size;
    bool m_isStatic;

    AABB() {
        AABB({32,32,32,32}, true);
    }

    AABB(Rectangle _size, bool _isStatic) {
        m_size = _size;
        m_isStatic = _isStatic;
    }
};

class AABBCollider {
    private:
        AABB m_collider;

        Color debugDrawColor;

    public:
        AABBCollider();
        AABBCollider(Vector2 size, Vector2 position, bool _isStatic);
        AABBCollider(AABB _aabb) {
            m_collider = _aabb;
            debugDrawColor.r = (unsigned char)GetRandomValue(0,255);
            debugDrawColor.g = (unsigned char)GetRandomValue(0,255);
            debugDrawColor.b = (unsigned char)GetRandomValue(0,255);
            debugDrawColor.a = 255;
        }

        void Draw();

        Rectangle GetRectangle() {return m_collider.m_size;}

        bool GetIsStatic() {return m_collider.m_isStatic;}


        void SetPosition(Vector2 _position);

        bool CheckPointInCollider(Vector2 _point);
    
};  



inline Vector2 GetAABBPosition(AABB _aabb) { return {_aabb.m_size.x, _aabb.m_size.y}; }

inline Vector2 GetAABBSize(AABB _aabb) {return {_aabb.m_size.width, _aabb.m_size.height};}

