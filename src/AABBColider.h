#include "raylib.h"


class AABBCollider {
    private:
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