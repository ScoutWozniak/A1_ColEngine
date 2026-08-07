#pragma once

struct PhysicsProperties {
    public:
    PhysicsProperties(float _mass, float _bouncy) {
        m_bouncy = _bouncy;
    }

    float m_bouncy = 0.0f;

    float m_mass = 1.0f;
};