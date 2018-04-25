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

    void SetPosition(glm::vec3 _position);
    void SetStartPosition(glm::vec3 _position);
    void SetMovementType(MovementType _type);
    void SetScale(glm::vec3 _scale);
    void SetTexture(std::string _texture);
    void SetColour(glm::vec3 _colour);
    void SetSpeed(float _speed);
    void SetProgram(GLuint _program);
    void SetRotation(glm::vec3 _angle);
    void SetRotationAxis(glm::vec3 _rotationAxis);

    glm::vec3 GetPosition() const;
    glm::vec3 GetScale() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetRotationAxis() const;
    glm::vec3 GetColour() const;

    void Rotate();

private:
    Camera* camera;
    MovementType movementType;

    float speed;

    std::vector<VertexFormat> vertices;
    std::vector<GLuint> indices;

    glm::vec3 startPosition;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 angle;
    glm::vec3 rotationAxis;
    glm::vec3 colour;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint texture;
    GLuint program;

    glm::vec3 direction;
};