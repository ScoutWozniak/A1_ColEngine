#include "Camera.h"


// TODO - Should not hold the SceneCamera, but rather reference the main camera in the scene
class CameraController {
    public:
        CameraController();
        void Update();

        SceneCamera m_camera;
    private:
        

        const float MOVE_SPEED = 1000.0f;
};