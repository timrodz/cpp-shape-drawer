//
//  File Name: 
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
// 
//

#pragma once

#include <vector>

#include "GameModel.h"
#include "Camera.h"

class GameScene {
public:
    virtual ~GameScene();
    static GameScene& GetInstance();

    void CreateModel(ModelType _type, MovementType _movement, GLuint _program, const char* _texture, glm::vec3 _colour, glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, float _speed);
    void AddCamera(Camera* _camera);
    std::vector<GameModel*> GetModels() const;

    void Render();
    void Update(float _deltaTime);

    void ClearScene();
    void ReloadScene();

    void CreateDefaultScene(GLuint _shaderProgram);

private:
    GameScene();
    GameScene(GameScene const&);
    GameScene operator=(GameScene const&);

protected:
    static GameScene* s_pGame;
    std::vector<GameModel*> m_vectorModels;
    Camera* m_camera;
};