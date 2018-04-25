//
//  File Name: ShaderLoader.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file for the scene loader class
//

#pragma once

#include <iostream>

#include <glew\glew.h>
#include <freeglut\freeglut.h>

class ShaderLoader
{

public:
    ShaderLoader();
    ~ShaderLoader();
    GLuint CreateProgram(char* _vertexShaderFilename, char* _fragmentShaderFilename);

private:
    std::string ReadShader(char* _filename);
    GLuint CreateShader(GLenum _shaderType, std::string source, char* _shaderName);
};