//
//  File Name: GameScene.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file for the GameScene class
//  The GameScene is a singleton, to use:
//  GameScene::GetInstance() will return the existing instance.
//

#pragma once

#include <vector>

#include "GameModel.h"
#include "Camera.h"
#include "Cubemap.h"

class GameScene
{
public:
    virtual ~GameScene();
    static GameScene& GetInstance();

    void CreateModel(GameModelOptions _options);
    void SetCamera(Camera* _camera);
    void SetCubemap(Cubemap* cubemap);
    std::vector<GameModel*> GetModels() const;

    void Update(float _currentTime);
    void Render();

    void ClearScene();

    void CreateDefaultScene(GLuint _shaderProgram);

private:
    GameScene();
    GameScene(GameScene const&);
    GameScene operator=(GameScene const&);

protected:
    static GameScene* Instance;
    std::vector<GameModel*> gameModelVector;
    Camera* camera;
    Cubemap* cubemap;
};