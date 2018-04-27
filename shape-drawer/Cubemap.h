//
//  File Name: Cubemap.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file for the cubemap class (Skybox)
//

#pragma once

#include "GameModel.h"
#include "Model.h"
#include "utils.h"

#include <vector>

class Cubemap : public GameModel
{
public:
	Cubemap(GLuint _program, Camera* _camera);
	~Cubemap();
    
	virtual void Render() override;

private:
	GLuint CreateCubemap(std::vector<const GLchar*> _faces);
	
private:
	GLuint texture;
};