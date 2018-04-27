//
//  File Name: GameScene.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file for the GameScene class
//  The GameScene is a singleton
//  To get instance, call GameScene::GetInstance()
//

#pragma once

#include <vector>

#include "GameObject.h"
#include "Camera.h"
#include "Cubemap.h"

class GameScene
{
public:
    virtual ~GameScene();
    static GameScene& GetInstance();

    void CreateModel(GameObjectOptions _options);
    void SetCamera(Camera* _camera);
    void SetCubemap(Cubemap* cubemap);
    std::vector<GameObject*> GetModels() const;

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
    std::vector<GameObject*> gameModelVector;
    Camera* camera;
    Cubemap* cubemap;
};