#pragma once

#include "Utils.h"

class Camera;

class GameModel {
public:
	GameModel(ModelType _modelType, Camera* _camera);
	~GameModel();

	void Update(GLfloat time);
	void Render();

	void SetPosition(glm::vec3 _position);
	void SetScale(glm::vec3 _scale);
	void SetColor(glm::vec3 _color);
	void SetCamera(Camera* camera);
	void SetSpeed(float _speed);
	void SetProgram(GLuint program);
	//void SetRotation(glm::vec3 angle);
	//void SetRotationAxis(glm::vec3 rotationAxis);

	void SetTexture(std::string texFileName);
	//void SetSpecularStrength(float strength);

    void SetMovementType(MovementType _type);

	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();
	//glm::vec3 GetRotationAxis();
	glm::vec3 GetColor();

    void Move();
	//void MoveForward();
	//void MoveBackward();
	//void MoveLeft();
	//void MoveRight();
	//void MoveUp();
	//void MoveDown();

	void Rotate(glm::vec3 axis);

private:
	Camera* camera;
    MovementType m_MovementType;
	//Light* light;

	bool isTextureSet = false;

	float speed;

	std::vector<VertexFormat>vertices;
	std::vector<GLuint>indices;
    
    glm::vec3 startPosition;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 angle;
	glm::vec3 rotationAxis;
	glm::vec3 color;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;
	GLuint program;

	//glm::mat4 model;

	//float specularStrength;
	//float ambientStrength;

    glm::vec3 direction;
	bool triangleFan;
};