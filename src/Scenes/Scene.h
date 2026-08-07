#pragma once

#include "raylib.h"


// Scenes - Currently scenes only work when inherited from ): ideally this gets replaced with a data-driven approach!
class Scene {
    public:
        virtual void Initialise() {}
        virtual void Update() {}
        virtual void Draw() {}

    private:
        
};