//
//  File Name: GameModel.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file containing the GameModel class, which acts like a Transform.
//  GameModel derives from Model
//

#pragma once

#include "Model.h"

class GameModel : public Model
{
public:
    GameModel();
    GameModel(ModelOptions _options);
    ~GameModel();

    void SetShaderProgram(GLuint _program);
    GLuint GetShaderProgram() const;

protected:
    GLuint shaderProgram;

    std::vector<VertexFormat> vertices;
    std::vector<GLuint> indices;

    GLuint vertexArrayObject;
    GLuint vertexBufferObject;
    GLuint elementBufferObject;
};