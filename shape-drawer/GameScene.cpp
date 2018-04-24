//
//  File Name: 
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
// 
//

#include "GameScene.h"

GameScene* GameScene::s_pGame = 0;

GameScene::GameScene() {}

GameScene::~GameScene() {}

// Get the current game instance
// author : Juan Rodriguez
// return : GameScene reference
GameScene& GameScene::GetInstance()
{
    if (s_pGame == 0)
    {
        s_pGame = new GameScene();
    }

    return (*s_pGame);
}

// Sets the camera for the current scene
// author        : Juan Rodriguez
// param _camera : The camera to pass
// return        : void
void GameScene::AddCamera(Camera* _camera)
{
    this->m_camera = _camera;
}

// Creates a model based on user defined parameters
// author: Juan Rodriguez
// param _type: the type of model to create
// param _texture: the file that contains the texture image
// param _position: the position vector to place the model at
// param _rotation: the rotation vector to rotate the model towards
// return: void
void GameScene::CreateModel(ModelType _type,
                            MovementType _movement,
                            GLuint _program,
                            const char* _texture,
                            glm::vec3 _colour,
                            glm::vec3 _position,
                            glm::vec3 _rotation,
                            float _speed
)
{
    GameModel* tempModel = new GameModel(_type, this->m_camera);
    tempModel->SetProgram(_program);
    tempModel->SetMovementType(_movement);
    tempModel->SetColor(_colour);
    tempModel->SetPosition(_position);
    tempModel->SetRotation(_rotation);
    tempModel->SetSpeed(_speed);
    if (_texture != "")
    {
        tempModel->SetTexture(_texture);
    }
    m_vectorModels.push_back(tempModel);
}

std::vector<GameModel*> GameScene::GetModels() const
{
    return (m_vectorModels);
}

void GameScene::Render()
{
    for (auto it = m_vectorModels.begin(); it < m_vectorModels.end(); it++)
    {
        (*it)->Render();
    }
}

void GameScene::Update(float _deltaTime)
{
    for (auto it = m_vectorModels.begin(); it < m_vectorModels.end(); it++)
    {
        (*it)->Update(_deltaTime);
    }
}

void GameScene::ClearScene()
{
    m_vectorModels.clear();
    std::cout << "The scene has been cleared!";
}

void GameScene::ReloadScene()
{
}

GameScene GameScene::operator=(GameScene const &)
{
    return GameScene();
}