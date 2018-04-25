//
//  File Name: Camera.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file containing the camera class
//

#pragma once

#include "Utils.h"

class Camera
{
public:
    //Camera();
    Camera(glm::vec3 _position, float _fieldOfView, int _width, int _height);
    ~Camera();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    glm::vec3 GetPosition() const;

private:
    int width, height;

    float fieldOfView;

    glm::vec3 position, up, forward;

    glm::mat4 viewMatrix, projectionMatrix;
};