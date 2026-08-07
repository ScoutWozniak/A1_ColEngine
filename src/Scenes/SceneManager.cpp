#include "SceneManager.h"

SceneManager::SceneManager()
{
    
}

void SceneManager::InitialiseScene()
{
    CurrentScene::CurrentScene_Instance->Initialise();
}

void SceneManager::Update()
{
    CurrentScene::CurrentScene_Instance->Update();
}

void SceneManager::Draw()
{
    CurrentScene::CurrentScene_Instance->Draw();
}
