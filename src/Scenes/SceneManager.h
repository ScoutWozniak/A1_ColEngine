#pragma once
#include "Scenes/Scene.h"

namespace CurrentScene {
    inline Scene* CurrentScene_Instance;
};

class SceneManager {
    public:
        SceneManager();

        template<typename T>
        T* LoadScene();

        void InitialiseScene();

        void Update();

        void Draw();

    private:
        Scene m_loadedScene;
        
};

template <typename T>
inline T *SceneManager::LoadScene()
{
    m_loadedScene = T{};
    CurrentScene::CurrentScene_Instance = &m_loadedScene;
    InitialiseScene();
    return (T*)CurrentScene::CurrentScene_Instance;
}


namespace CurrentScene {
    inline SceneManager* SceneManager_Instance;
};

