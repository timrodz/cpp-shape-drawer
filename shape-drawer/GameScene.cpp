//
//  File Name: GameScene.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Renders and updates objects inside the scene.
//

#include "GameScene.h"

GameScene* GameScene::Instance = 0;

GameScene::GameScene() {}

GameScene::~GameScene() {}

// Method Name: GetInstance
// Description: Gets the GameScene instance
// author: Juan Alejandro Rodriguez Morais
// return: GameScene reference
GameScene& GameScene::GetInstance()
{
    if (Instance == 0)
    {
        Instance = new GameScene();
    }

    return (*Instance);
}

// Method Name: SetCamera
// Description: Sets the main camera of the scene
// author: Juan Alejandro Rodriguez Morais
// param _camera: The main camera to show at the scene
// return: void
void GameScene::SetCamera(Camera* _camera)
{
    this->camera = _camera;
}

// Method Name: SetCubemap
// Description: Sets the main cubemap of the scene
// author: Juan Alejandro Rodriguez Morais
// param _cubemap: The main cubemap to show at the scene
// return: void
void GameScene::SetCubemap(Cubemap* _cubemap)
{
    this->cubemap = _cubemap;
}

// Method Name: CreateModel
// Description: Creates a model based on user defined parameters
// author: Juan Alejandro Rodriguez Morais
// param _model: The type of model
// param _movement: The type of movemnt
// param _program: The shader to apply
// param _colour: The colour of the object
// param _scale: The dimensions of the object
// param _position: the position vector to place the model at
// param _rotation: the rotation vector to rotate the model towards
// param _speed: The desired movement speed of the object
// return: void
void GameScene::CreateModel(
    ModelType _model,
    MovementType _movement,
    GLuint _program,
    glm::vec3 _colour,
    glm::vec3 _scale,
    glm::vec3 _position,
    glm::vec3 _rotation,
    float _speed
)
{
    GameModel* tempModel = new GameModel(_model, this->camera);
    tempModel->SetProgram(_program);
    tempModel->SetMovementType(_movement);
    tempModel->SetColour(_colour);
    tempModel->SetScale(_scale);
    tempModel->SetPosition(_position);
    tempModel->SetStartPosition(_position);
    tempModel->SetRotation(_rotation);
    tempModel->SetSpeed(_speed);
    gameModelVector.push_back(tempModel);
}

// Method Name: GetModels
// Description: Returns the model vector
// author: Juan Alejandro Rodriguez Morais
// return: std::vector<GameModel*>
std::vector<GameModel*> GameScene::GetModels() const
{
    return (gameModelVector);
}

// Method Name: Render
// Description: Renders all objects, including the skybox
// author: Juan Alejandro Rodriguez Morais
// return: void
void GameScene::Render()
{
    cubemap->Render();

    for (auto it = gameModelVector.begin(); it < gameModelVector.end(); it++)
    {
        (*it)->Render();
    }
}

// Method Name: Update
// Description: Updates all objects
// author: Juan Alejandro Rodriguez Morais
// param _deltaTime: The time it took to render last frame
// return: void
void GameScene::Update(float _deltaTime)
{
    for (auto it = gameModelVector.begin(); it < gameModelVector.end(); it++)
    {
        (*it)->Update(_deltaTime);
    }
}

// Method Name: ClearScene
// Description: Clears the gameModelVector objects
// author: Juan Alejandro Rodriguez Morais
// return: void
void GameScene::ClearScene()
{
    gameModelVector.clear();
}

// Method Name: CreateDefaultScene
// Description: Creates a scene with all shapes/movements
// author: Juan Alejandro Rodriguez Morais
// param _shaderProgram: The shader to use for all objects
// return: void
void GameScene::CreateDefaultScene(GLuint _shaderProgram)
{
    CreateModel(ModelType::Triangle, MovementType::LeftRight, _shaderProgram, Utils::RGBtoAlpha(51, 153, 51), glm::vec3(1, 1, 1), glm::vec3(-4, -0.5, 0), glm::vec3(0, 0, 0), 3.0f);
    CreateModel(ModelType::Square, MovementType::UpDown, _shaderProgram, Utils::RGBtoAlpha(227, 181, 5), glm::vec3(1, 1, 1), glm::vec3(6, 0, 0), glm::vec3(0, 0, 0), 3);
    CreateModel(ModelType::Circle, MovementType::Box, _shaderProgram, Utils::RGBtoAlpha(86, 163, 166), glm::vec3(1, 1, 1), glm::vec3(0, -2, 0), glm::vec3(0, 0, 0), 0.05f);
    CreateModel(ModelType::Hexagon, MovementType::Circular, _shaderProgram, Utils::RGBtoAlpha(219, 80, 74), glm::vec3(1, 1, 1), glm::vec3(0, 2, 0), glm::vec3(0, 0, 0), 3.0f);
    CreateModel(ModelType::Cube, MovementType::BoxInverted, _shaderProgram, Utils::RGBtoAlpha(224, 74, 153), glm::vec3(1, 1, 1), glm::vec3(-5, 3.5, 0), glm::vec3(0, 0, 0), 0.05f);
    CreateModel(ModelType::Pentagon, MovementType::LeftRight, _shaderProgram, Utils::RGBtoAlpha(242, 134, 58), glm::vec3(1, 1, 1), glm::vec3(-6, -3.5, 0), glm::vec3(0, 0, 17.5), 3.0f);
    CreateModel(ModelType::Heptagon, MovementType::Circular, _shaderProgram, Utils::RGBtoAlpha(86, 56, 237), glm::vec3(1, 1, 1), glm::vec3(5, 3.5, 0), glm::vec3(0, 0, 0), 5);
}

// Method Name: Operator=
// Description: Prevents the object from being initialised
// author: Juan Alejandro Rodriguez Morais
// return: Current GameScene instance
GameScene GameScene::operator=(GameScene const &)
{
    return GameScene();
}