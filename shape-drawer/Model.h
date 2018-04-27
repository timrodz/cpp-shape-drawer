//
//  File Name: Model.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file containing information about the Model class
//  The model class acts as a base class
//

#pragma once

#include "Utils.h"
#include "Camera.h"

/* Model Options */
struct ModelOptions
{
    Camera* camera;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    // Defaults
    ModelOptions()
    {
        position = glm::vec3(0, 0, 0);
        scale = glm::vec3(1, 1, 1);
        rotation = glm::vec3(0, 0, 0);
    }
    // Defaults with a camera
    ModelOptions(Camera* _camera)
    {
        camera = _camera;
        position = glm::vec3(0, 0, 0);
        scale = glm::vec3(1, 1, 1);
        rotation = glm::vec3(0, 0, 0);
    }
    ModelOptions(Camera* _camera, glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation)
    {
        camera = _camera;
        position = _position;
        scale = _scale;
        rotation = _rotation;
    }
};

class Model
{
public:
    Model();
    Model(ModelOptions _options);
    virtual ~Model();

    virtual void Update(GLfloat _currentTime);

    // Must be implemented by every child class
    virtual void Render() = 0;

    void SetCamera(Camera* _camera);
    void SetPosition(glm::vec3 _position);
    void SetScale(glm::vec3 _scale);
    void SetRotation(glm::vec3 _angle);

    Camera* GetCamera() const;
    glm::vec3 GetPosition() const;
    glm::vec3 GetScale() const;
    glm::vec3 GetRotation() const;

protected:
    Camera* camera;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};