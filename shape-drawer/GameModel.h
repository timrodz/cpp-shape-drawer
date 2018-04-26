//
//  File Name: GameModel.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file for the GameModel class
//

#pragma once

#include "Utils.h"

class Camera;

class GameModel
{
public:
    GameModel(ModelType _modelType, Camera* _camera);
    ~GameModel();

    void Update(GLfloat _time);
    void Render();

    void SetProgram(GLuint _program);
    void SetRotation(glm::vec3 _angle);
    void SetPosition(glm::vec3 _position);
    void SetStartPosition(glm::vec3 _position);
    void SetScale(glm::vec3 _scale);
    void SetColour(glm::vec3 _colour);
    void SetSpeed(float _speed);
    void SetMovementType(MovementType _type);

    glm::vec3 GetPosition() const;
    glm::vec3 GetScale() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetStartPosition() const;
    MovementType GetMovementType() const;
    glm::vec3 GetColour() const;
    float GetSpeed() const;

private:
    Camera* camera;
    MovementType movementType;
    float speed;

    std::vector<VertexFormat> vertices;
    std::vector<GLuint> indices;

    glm::vec3 startPosition;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    glm::vec3 colour;

    GLuint vao;
    GLuint vbo;
    GLuint program;

    glm::vec3 direction;
};