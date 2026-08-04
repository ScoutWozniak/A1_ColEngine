#include "Camera.h"

class CameraController {
    public:
        CameraController();
        void Update();

        SceneCamera m_camera;
    private:
        

        const float MOVE_SPEED = 1000.0f;
};