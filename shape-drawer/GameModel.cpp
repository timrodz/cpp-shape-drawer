//
//  File Name: GameModel.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Functionality for the GameModel class
//  GameModel is a 
//

#include "GameModel.h"

GameModel::GameModel() {}

GameModel::GameModel(ModelOptions _options) :
    Model(_options)
{}

GameModel::~GameModel() {}

// Method Name: SetProgram
// Description: Sets the shader that this object will be rendered with
// author: Juan Alejandro Rodriguez Morais
// param _program: The shader type
// return: void
void GameModel::SetShaderProgram(GLuint _program)
{
    this->shaderProgram = _program;
}

// Method Name: GetProgram
// Description: Returns the program of the object
// author: Juan Alejandro Rodriguez Morais
// return: GLuint
GLuint GameModel::GetShaderProgram() const
{
    return this->shaderProgram;
}