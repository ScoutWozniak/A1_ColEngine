#pragma once

#include "raylib.h"


class AABBCollider {
    private:
        AABB m_collider;
        Rectangle recCollider;

        Color debugDrawColor;

        bool isStatic = true;

    public:
        AABBCollider();
        AABBCollider(Vector2 size, Vector2 position, bool _isStatic);

        void Draw();

        Rectangle GetRectangle() {return recCollider;}

        bool GetIsStatic() {return isStatic;}


        void SetPosition(Vector2 _position);
    
};  

struct AABB {
    Rectangle m_size;
    bool m_isStatic;
};

inline Vector2 GetAABBPosition(AABB _aabb) { return {_aabb.m_size.x, _aabb.m_size.y}; }

inline Vector2 GetAABBSize(AABB _aabb) {return {_aabb.m_size.width, _aabb.m_size.height};}

