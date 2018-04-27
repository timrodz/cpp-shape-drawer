//
//  File Name: Cubemap.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Creation and rendering of a cubemap
//

#include "Cubemap.h"

// Method Name: Cubemap
// Description: Constructor for the cubemap
// author: Juan Alejandro Rodriguez Morais
// param _cubemapProgram: The shader to use for rendering the cubemap
// param _camera: The camera that will draw the cubemap
// return: Cubemap
Cubemap::Cubemap(GLuint _cubemapProgram, Camera* _camera)
{
    GLfloat vertices[] = 
    {
        // Positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    this->shaderProgram = _cubemapProgram;
    this->camera = _camera;

    //Set up skybox VAO
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*) 0);
    glBindVertexArray(0);

    // Set textures
    std::vector<const GLchar*> faces;

    faces.push_back("textures/right.jpg");
    faces.push_back("textures/left.jpg");
    faces.push_back("textures/top.jpg");
    faces.push_back("textures/bottom.jpg");
    faces.push_back("textures/back.jpg");
    faces.push_back("textures/front.jpg");

    texture = CreateCubemap(faces);
}

Cubemap::~Cubemap() {}

// Method Name: CreateCubemap
// Description: Creates the cubemap and binds the textures
// author: Juan Alejandro Rodriguez Morais
// param _faces: All the faces of the cubemap
// return: GLuint
GLuint Cubemap::CreateCubemap(std::vector<const GLchar*> _faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height;
    unsigned char* image;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (GLuint i = 0; i < _faces.size(); ++i)
    {
        image = SOIL_load_image(_faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}

// Method Name: Render
// Description: Draws the cubemap on the screen
// author: Juan Alejandro Rodriguez Morais
// return: void
void Cubemap::Render()
{
    glUseProgram(shaderProgram);

    glBindVertexArray(vertexArrayObject);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "cubeSampler"), 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    glm::mat4 world;
    world = glm::scale(world, glm::vec3(10.0f, 10.0f, 10.0f));

    glm::mat4 mvp;
    mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix() * world;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}