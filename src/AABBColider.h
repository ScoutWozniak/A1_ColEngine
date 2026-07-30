#include "raylib.h"


class AABBCollider {
    private:
        Rectangle recCollider;

        Color debugDrawColor;

        public:
        AABBCollider(Vector2 size, Vector2 position);

        void Draw();
};