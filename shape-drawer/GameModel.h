//
//  File Name: 
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  
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