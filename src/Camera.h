
#include "raylib.h"

class SceneCamera {
    public:
        Camera2D m_camera2D;

        void UpdateCamera();

        void SetPosition(Vector2 _position);

        Vector2 GetPosition();

        Vector2 ScreenToWorldPosition(Vector2 _screenPos);

        SceneCamera();
    private:

};