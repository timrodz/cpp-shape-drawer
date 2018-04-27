//
//  File Name: Model.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Contains basic functionality of the Model class
//  Please note that Render is a pure virtual function
//  You have to implement it for every child class
//

#include "Model.h"

Model::Model() {}

Model::Model(ModelOptions _options) :
    position(_options.position),
    rotation(_options.rotation),
    scale(_options.scale)
{
    this->camera = _options.camera;
}

Model::~Model() {}

// Pure virtual
void Model::Update(GLfloat _currentTime)
{
    glutPostRedisplay();
}

// Pure virtual
void Model::Render() {}

// Method Name: SetCamera
// Description: Sets the camera of the object
// author: Juan Alejandro Rodriguez Morais
// return: void
void Model::SetCamera(Camera * _camera)
{
    this->camera = _camera;
}

// Method Name: SetPosition
// Description: Sets the position of the object
// author: Juan Alejandro Rodriguez Morais
// param _position: The desired position
// return: void
void Model::SetPosition(glm::vec3 _position)
{
    this->position = _position;
}

// Method Name: SetScale
// Description: Sets the scale of the object
// author: Juan Alejandro Rodriguez Morais
// param _scale: The desired scale
// return: void
void Model::SetScale(glm::vec3 _scale)
{
    this->scale = _scale;
}

// Method Name: SetRotation
// Description: Sets the rotation (euler angles) of the object
// author: Juan Alejandro Rodriguez Morais
// param _angle: The desired angle
// return: void
void Model::SetRotation(glm::vec3 _angle)
{
    this->rotation = _angle;
}

// Method Name: GetCamera
// Description: Returns the current camera of the object
// author: Juan Alejandro Rodriguez Morais
// return: Camera pointer
Camera* Model::GetCamera() const
{
    return this->camera;
}

// Method Name: GetPosition
// Description: Returns the current position of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
glm::vec3 Model::GetPosition() const
{
    return this->position;
}

// Method Name: GetScale
// Description: Returns the scale of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
glm::vec3 Model::GetScale() const
{
    return this->scale;
}

// Method Name: GetRotation
// Description: Returns the rotation of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
glm::vec3 Model::GetRotation() const
{
    return this->rotation;
}