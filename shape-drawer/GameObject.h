//
//  File Name: GameObject.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file for the GameObject class
//  GameObject derives from GameModel
//

#pragma once

#include "Model.h"
#include "GameModel.h"
#include "Utils.h"

class Camera;

/* Game Model Options */
struct GameObjectOptions
{
    ModelOptions modelOptions;
    GLuint shaderProgram;
    ModelType modelType;
    MovementType movementType;
    glm::vec3 colour;
    float speed;

    // Defaults
    GameObjectOptions()
    {
        modelType = ModelType::Triangle;
        movementType = MovementType::Idle;
        colour = glm::vec3(1, 1, 1);
        speed = 0.0f;
    }
    GameObjectOptions(ModelOptions _options, GLuint _shaderProgram, ModelType _modelType, MovementType _movementType, glm::vec3 _colour, float _speed)
    {
        modelOptions = _options;
        shaderProgram = _shaderProgram;
        modelType = _modelType;
        movementType = _movementType;
        colour = _colour;
        speed = _speed;
    }
};

class GameObject : GameModel
{
public:
    GameObject();
    GameObject(GameObjectOptions _options);
    ~GameObject();

    virtual void Update(GLfloat _currentTime) override;
    virtual void Render() override;

    void SetStartPosition(glm::vec3 _position);
    void SetMovementType(MovementType _type);
    void SetColour(glm::vec3 _colour);
    void SetSpeed(float _speed);

    glm::vec3 GetStartPosition() const;
    ModelType GetModelType() const;
    MovementType GetMovementType() const;
    glm::vec3 GetColour() const;
    float GetSpeed() const;

private:
    glm::vec3 startPosition;
    ModelType modelType;
    MovementType movementType;
    glm::vec3 colour;
    float speed;
};