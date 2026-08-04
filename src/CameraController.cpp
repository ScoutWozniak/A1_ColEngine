#include "CameraController.h"
#include "raylib.h"
#include "raymath.h"

CameraController::CameraController()
{
    m_camera = SceneCamera();
}

void CameraController::Update()
{
    Vector2 moveDir = {0,0};
    if (IsKeyDown(KEY_A))  { 
        moveDir.x = -1;
    }
    else if (IsKeyDown(KEY_D)) { 
        moveDir.x = 1;
    }

    if (IsKeyDown(KEY_W)) {
        moveDir.y = -1;
    }
    else if (IsKeyDown(KEY_S)) {
        moveDir.y = 1;
    }

    Vector2 moveVelocity = Vector2Normalize(moveDir) * MOVE_SPEED * GetFrameTime();

    m_camera.SetPosition(Vector2Add(m_camera.GetPosition(), moveVelocity));

    float zoomInput = GetMouseWheelMove();
    m_camera.m_camera2D.zoom += zoomInput * 0.05f;
}