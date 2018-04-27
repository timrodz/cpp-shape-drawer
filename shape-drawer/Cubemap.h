//
//  File Name: Cubemap.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file for the cubemap class (Skybox)
//

#pragma once

#include "camera.h"
#include "utils.h"

#include <vector>

class Cubemap
{
public:

	Cubemap(GLuint _program, Camera* _camera);
	~Cubemap();

	void Render();

private:
	GLuint CreateCubemap(std::vector<const GLchar*> _faces);
	
private:
	Camera* camera;

    std::vector<VertexFormat> vertices;
	std::vector<GLuint> indices;

	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;
	GLuint shaderProgram;
	GLuint texture;
};