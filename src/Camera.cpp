#include "Camera.h"
#include "raymath.h"

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

Vector2 SceneCamera::ScreenToWorldPosition(Vector2 _screenPos)
{
    return GetScreenToWorld2D(_screenPos, m_camera2D);
}

void SceneCamera::SetPosition(Vector2 _pos) {
    m_camera2D.target = _pos;
}