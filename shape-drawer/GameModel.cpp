//
//  File Name: GameModel.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Handles the main logic for GameModel drawing, updating and their creation
//

#include "GameModel.h"
#include "Camera.h"

// Method Name: GameModel
// Description: Constructor for the GameModel
// author: Juan Alejandro Rodriguez Morais
// param _modelType: The type of model to create
// param _camera: The camera that will render the model
// return: GameModel
GameModel::GameModel(ModelType _modelType, Camera* _camera)
{
    this->camera = _camera;
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->position = glm::vec3(0.0, 0.0, 0.0);
    this->colour = glm::vec3(1.0f, 1.0f, 1.0f);
    this->speed = 0.0f;
    this->movementType = MovementType::Idle;

    switch (_modelType)
    {
        case Triangle:Utils::SetTriangleData(vertices, indices);break;
        case Square: Utils::SetSquareData(vertices, indices); break;
        case Circle: Utils::SetCircleData(vertices, indices); break;
        case Hexagon: Utils::SetHexagonData(vertices, indices); break;
        case Cube: Utils::SetCubeData(vertices, indices); break;
        case Pentagon: Utils::SetPentagonData(vertices, indices); break;
        case Heptagon: Utils::SetHeptagonData(vertices, indices); break;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GameModel::~GameModel() {}

// Method Name: Render
// Description: Draws the model based on its settings
// author: Juan Alejandro Rodriguez Morais
// return: void
void GameModel::Render()
{
    glUseProgram(this->program);

    glm::mat4 model, view, projection;
    model = glm::translate(model, position);

    model = glm::translate(model, glm::vec3(0.0f * this->scale.x, 0.0f * scale.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    model = glm::translate(model, glm::vec3(-0.0f * scale.x, -0.0f * scale.y, 0.0f));

    model = glm::scale(model, scale);

    view = this->camera->GetViewMatrix();
    projection = this->camera->GetProjectionMatrix();

    // Get their uniform location
    GLint viewLoc = glGetUniformLocation(program, "view");
    GLint projLoc = glGetUniformLocation(program, "projection");

    // Pass them to the shaders
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLint modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // lighting calculations
    GLint objColorLoc = glGetUniformLocation(program, "objectColor");
    glUniform3f(objColorLoc, colour.x, colour.y, colour.z);

    GLuint cameraPosLoc = glGetUniformLocation(program, "viewPosition");
    glUniform3f(cameraPosLoc, camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Method Name: Update
// Description: Updates the model based on current time
// author: Juan Alejandro Rodriguez Morais
// param _currentTime: The elapsed time since start
// return: void
void GameModel::Update(GLfloat _currentTime)
{
    switch (movementType)
    {
        case (MovementType::UpDown):
        {
            position.y = (Utils::VERTICAL_LIMIT * sin(_currentTime * speed) + startPosition.y);
        }
        break;
        case (MovementType::LeftRight):
        {
            position.x = (Utils::HORIZONTAL_LIMIT * cos(_currentTime * speed) + startPosition.x);
        }
        break;
        case (MovementType::Circular):
        {
            position.x = (Utils::CIRCULAR_RADIUS * cos(_currentTime * speed) + startPosition.x);
            position.y = (Utils::CIRCULAR_RADIUS * sin(_currentTime * speed) + startPosition.y);
        }
        break;
        case (MovementType::Box):
        case (MovementType::BoxInverted):
        {
            position = Utils::MoveTowards(position, startPosition + Utils::BoxPositions[Utils::movementIndex], (MovementType::Box) ? speed : -speed);

            if (position == (startPosition + Utils::BoxPositions[Utils::movementIndex]))
            {
                Utils::movementIndex = (Utils::movementIndex + 1) % (Utils::GetBoxPositionsLength());
            }
        }
        break;
    }

    glutPostRedisplay();
}

// Method Name: SetProgram
// Description: Sets the shader that this object will be rendered with
// author: Juan Alejandro Rodriguez Morais
// param _program: The shader type
// return: void
void GameModel::SetProgram(GLuint _program)
{
    this->program = _program;
}

// Method Name: SetPosition
// Description: Sets the position of the object
// author: Juan Alejandro Rodriguez Morais
// param _position: The desired position
// return: void
void GameModel::SetPosition(glm::vec3 _position)
{
    this->position = _position;
}

// Method Name: SetScale
// Description: Sets the scale of the object
// author: Juan Alejandro Rodriguez Morais
// param _scale: The desired scale
// return: void
void GameModel::SetScale(glm::vec3 _scale)
{
    this->scale = _scale;
}

// Method Name: SetRotation
// Description: Sets the rotation (euler angles) of the object
// author: Juan Alejandro Rodriguez Morais
// param _angle: The desired angle
// return: void
void GameModel::SetRotation(glm::vec3 _angle)
{
    this->rotation = _angle;
}

// Method Name: SetStartPosition
// Description: Sets the start position of the object
// author: Juan Alejandro Rodriguez Morais
// param _position: The desired position
// return: void
void GameModel::SetStartPosition(glm::vec3 _position)
{
    this->startPosition = _position;
}

// Method Name: SetColour
// Description: Sets the colour of the object (ALPHA values)
// author: Juan Alejandro Rodriguez Morais
// param _colour: The desired color
// return: void
void GameModel::SetColour(glm::vec3 _colour)
{
    this->colour = _colour;
}

// Method Name: SetSpeed
// Description: Sets the speed of the object
// author: Juan Alejandro Rodriguez Morais
// param _speed: The desired speed
// return: void
void GameModel::SetSpeed(float _speed)
{
    this->speed = _speed;
}

// Method Name: SetMovementType
// Description: Sets the movement type and direction accordingly
// author: Juan Alejandro Rodriguez Morais
// param _type: The type of movement
// return: void
void GameModel::SetMovementType(MovementType _type)
{
    this->movementType = _type;
}

// Method Name: GetPosition
// Description: Returns the current position of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
glm::vec3 GameModel::GetPosition() const
{
    return this->position;
}

// Method Name: GetScale
// Description: Returns the scale of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
glm::vec3 GameModel::GetScale() const
{
    return this->scale;
}

// Method Name: GetRotation
// Description: Returns the rotation of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
glm::vec3 GameModel::GetRotation() const
{
    return this->rotation;
}

glm::vec3 GameModel::GetStartPosition() const
{
    return this->startPosition;
}

MovementType GameModel::GetMovementType() const
{
    return this->movementType;
}


// Method Name: GetColour
// Description: Returns the colour of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
glm::vec3 GameModel::GetColour() const
{
    return this->colour;
}

float GameModel::GetSpeed() const
{
    return this->speed;
}