//
//  File Name: ShaderLoader.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Creates a program with Vertex and Fragment shaders
//

#include "ShaderLoader.h" 

#include<iostream>
#include<fstream>
#include<vector>

ShaderLoader::ShaderLoader() {}

ShaderLoader::~ShaderLoader() {}

// Method Name: CreateProgram
// Description: Creates the shader program
// author: Juan Alejandro Rodriguez Morais
// param _vertexShaderFilename: The file containing the vertex shader information
// param _fragmentShaderFilename: The file containing the fragment shader information
// return: GLuint
GLuint ShaderLoader::CreateProgram(char* _vertexShaderFilename, char* _fragmentShaderFilename)
{
    //read the shader files and save the code
    std::string vertex_shader_code = ReadShader(_vertexShaderFilename);
    std::string fragment_shader_code = ReadShader(_fragmentShaderFilename);

    GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
    GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

    int link_result = 0;
    //create the program handle, attatch the shaders and link it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_result);

    //check for link errors
    if (link_result == GL_FALSE)
    {
        int info_log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
        std::vector<char> program_log(info_log_length);
        glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
        std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
        return 0;
    }

    return program;
}

// Method Name: ReadShader
// Description: Reads the shader file
// author: Juan Alejandro Rodriguez Morais
// param _file: The file name
// return: string
std::string ShaderLoader::ReadShader(char* _file)
{
    std::string shaderCode;
    std::ifstream file(_file, std::ios::in);

    if (!file.good())
    {
        std::cout << "Can't read file " << _file << std::endl;
        std::terminate();
    }

    file.seekg(0, std::ios::end);
    shaderCode.resize((unsigned int) file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&shaderCode[0], shaderCode.size());
    file.close();
    return shaderCode;
}

// Method Name: CreateShader
// Description: Creates a shader with given information
// author: Juan Alejandro Rodriguez Morais
// param _shaderType: The type of shader to create
// param _file: The converted file
// param _name: The name associated with the shader type
// return: GLuint
GLuint ShaderLoader::CreateShader(GLenum _shaderType, std::string _file, char* _name)
{
    int compile_result = 0;

    GLuint shader = glCreateShader(_shaderType);
    const char *shader_code_ptr = _file.c_str();
    const int shader_code_size = _file.size();

    glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

    //check for errors
    if (compile_result == GL_FALSE)
    {
        int info_log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        std::vector<char> shader_log(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
        std::cout << "ERROR compiling shader: " << _name << std::endl << &shader_log[0] << std::endl;
        return 0;
    }

    return shader;
}