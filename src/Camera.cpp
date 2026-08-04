#include "Camera.h"

SceneCamera::SceneCamera() {
    m_camera2D = Camera2D();
    SetPosition({GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f});

    m_camera2D.rotation = 0.0f;
    m_camera2D.offset = {(GetScreenWidth() * 0.5f), (GetScreenHeight() * 0.5f)};
    m_camera2D.zoom = 1.0f;
}

void SceneCamera::UpdateCamera()
{
}

Vector2 SceneCamera::GetPosition() {
    return m_camera2D.target;
}

void SceneCamera::SetPosition(Vector2 _pos) {
    m_camera2D.target = _pos;
}