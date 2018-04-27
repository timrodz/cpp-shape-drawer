//
//  File Name: GameScene.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Renders and updates objects inside the scene.
//

#include "GameScene.h"

using glm::vec3;

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
// param _options: The options to create the Game Model with
// return: void
void GameScene::CreateModel(GameModelOptions _options)
{
    // Set the camera to be the current
    _options.modelOptions.camera = this->camera;

    // Create the model with our options
    GameModel* model = new GameModel(_options);
    gameModelVector.push_back(model);
}

// Method Name: GetModels
// Description: Returns the model vector
// author: Juan Alejandro Rodriguez Morais
// return: std::vector<GameModel*>
std::vector<GameModel*> GameScene::GetModels() const
{
    return (gameModelVector);
}

// Method Name: Update
// Description: Updates all objects
// author: Juan Alejandro Rodriguez Morais
// param _currentTime: The elapsed time of the application
// return: void
void GameScene::Update(float _currentTime)
{
    for (auto it = gameModelVector.begin(); it < gameModelVector.end(); ++it)
    {
        (*it)->Update(_currentTime);
    }
}

// Method Name: Render
// Description: Renders all objects, including the skybox
// author: Juan Alejandro Rodriguez Morais
// return: void
void GameScene::Render()
{
    cubemap->Render();

    for (auto it = gameModelVector.begin(); it < gameModelVector.end(); ++it)
    {
        (*it)->Render();
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
    GameModelOptions options;
    options.modelOptions = ModelOptions(camera, vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0));
    options.shaderProgram = _shaderProgram;

    // Triangle w/ LeftRight movement
    options.modelType = ModelType::Triangle;
    options.movementType = MovementType::LeftRight;
    options.modelOptions.position = vec3(-4, -0.5, 0);
    options.colour = Utils::RGBtoAlpha(51, 153, 51);
    options.speed = 3.0f;
    CreateModel(options);

    // Square w/ Updown movement
    options.modelType = ModelType::Square;
    options.movementType = MovementType::UpDown;
    options.modelOptions.position = vec3(6, 0, 0);
    options.colour = Utils::RGBtoAlpha(227, 181, 5);
    options.speed = 2.0f;

    CreateModel(options);

    // Circle with Box movement
    options.modelType = ModelType::Circle;
    options.movementType = MovementType::Box;
    options.modelOptions.position = vec3(0, -2, 0);
    options.colour = Utils::RGBtoAlpha(86, 163, 166);
    options.speed = 0.05f;

    CreateModel(options);

    // Hexagon with Circular movement
    options.modelType = ModelType::Hexagon;
    options.movementType = MovementType::Circular;
    options.modelOptions.position = vec3(0, 2, 0);
    options.colour = Utils::RGBtoAlpha(219, 80, 74);
    options.speed = 4.5f;

    CreateModel(options);

    // Cube with Box movement
    options.modelType = ModelType::Cube;
    options.movementType = MovementType::Box;
    options.modelOptions.position = vec3(-5, 3.5, 0);
    options.colour = Utils::RGBtoAlpha(224, 74, 153);
    options.speed = 0.05f;

    CreateModel(options);

    // Pentagon with LeftRight movement
    options.modelType = ModelType::Pentagon;
    options.movementType = MovementType::UpDown;
    options.modelOptions.position = vec3(-6, -3, 0);
    options.colour = Utils::RGBtoAlpha(242, 134, 58);
    options.speed = 2.75f;

    CreateModel(options);

    // Heptagon with Circular movement
    options.modelType = ModelType::Heptagon;
    options.movementType = MovementType::Circular;
    options.modelOptions.position = vec3(5.5, 3, 0);
    options.colour = Utils::RGBtoAlpha(86, 56, 237);
    options.speed = 6.5f;

    CreateModel(options);
}

// Method Name: Operator=
// Description: Prevents the object from being initialised
// author: Juan Alejandro Rodriguez Morais
GameScene GameScene::operator=(GameScene const &)
{
    return GameScene();
}