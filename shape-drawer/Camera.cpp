//
//  File Name: Camera.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Handles the camera that will be shown in the scene
//

#include "Camera.h"

Camera::~Camera() {}

// Method Name: Camera
// Description: Constructor for the camera
// author: Juan Alejandro Rodriguez Morais
// param _position: The Vector3 position of the camera
// param _fieldOfView: The field of view of the camera
// param _width: The width of the camera
// param _height: The height of the camera
// return: Camera
Camera::Camera(glm::vec3 _position, float _fieldofView, int _width, int _height)
{
    this->position = _position;
    this->up = glm::vec3(0, 1, 0);
    this->forward = glm::vec3(0, 0, -1);

    this->fieldOfView = _fieldofView;
    this->width = _width;
    this->height = _height;

    this->viewMatrix = GetViewMatrix();
    this->projectionMatrix = GetProjectionMatrix();
}

// Method Name: GetViewMatrix
// Description: Returns the LookAt vector of the camera
// author: Juan Alejandro Rodriguez Morais
// return: glm::mat4
glm::mat4 Camera::GetViewMatrix() const
{
    return (glm::lookAt(this->position, this->position + this->forward, this->up));
}

// Method Name: GetProjectionMatrix
// Description: Returns the perspective vector of the camera
// author: Juan Alejandro Rodriguez Morais
// return: glm::mat4
glm::mat4 Camera::GetProjectionMatrix() const
{
    return (glm::perspective(this->fieldOfView, (GLfloat) this->width / (GLfloat) this->height, 0.1f, 1000.0f));
}

// Method Name: GetPosition
// Description: Returns the position of the camera
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
glm::vec3 Camera::GetPosition() const
{
    return (position);
}