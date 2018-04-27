//
//  File Name: GameObject.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Handles the main logic for GameModel drawing, updating and their creation
//

#include "GameObject.h"
#include "Camera.h"

using glm::vec3;

GameObject::GameObject() {}

// Method Name: GameModel
// Description: Constructor for the GameModel
// author: Juan Alejandro Rodriguez Morais
// param _options: The options to create the game model with
// return: GameModel
GameObject::GameObject(GameObjectOptions _options) :
    GameModel(_options.modelOptions), // Set all default model options
    modelType(_options.modelType),
    movementType(_options.movementType),
    colour(_options.colour),
    speed(_options.speed)
{
    
    SetShaderProgram(_options.shaderProgram);
    this->startPosition = this->position;

    switch (modelType)
    {
        case Triangle:Utils::SetTriangleData(vertices, indices); break;
        case Square: Utils::SetSquareData(vertices, indices); break;
        case Circle: Utils::SetCircleData(vertices, indices); break;
        case Hexagon: Utils::SetHexagonData(vertices, indices); break;
        case Cube: Utils::SetCubeData(vertices, indices); break;
        case Pentagon: Utils::SetPentagonData(vertices, indices); break;
        case Heptagon: Utils::SetHeptagonData(vertices, indices); break;
    }

    // Initialise VAO, VBO and EBO (Graphics)
    glGenVertexArrays(1, &this->vertexArrayObject);
    glBindVertexArray(this->vertexArrayObject);

    glGenBuffers(1, &this->vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);

    // Store the position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GameObject::~GameObject() {}

// Method Name: Update
// Description: Updates the model based on current time
// author: Juan Alejandro Rodriguez Morais
// param _currentTime: The elapsed time since start
// return: void
void GameObject::Update(GLfloat _currentTime)
{
    switch (movementType)
    {
        case (MovementType::UpDown):
        {
            this->position.y = (Utils::VERTICAL_LIMIT * sin(_currentTime * this->speed) + this->startPosition.y);
        }
        break;
        case (MovementType::LeftRight):
        {
            this->position.x = (Utils::HORIZONTAL_LIMIT * cos(_currentTime * this->speed) + this->startPosition.x);
        }
        break;
        case (MovementType::Circular):
        {
            this->position.x = (Utils::CIRCULAR_RADIUS * cos(_currentTime * this->speed) + this->startPosition.x);
            this->position.y = (Utils::CIRCULAR_RADIUS * sin(_currentTime * this->speed) + this->startPosition.y);
        }
        break;
        case (MovementType::Box):
        {
            vec3 targetPosition = this->startPosition + Utils::BoxPositions[Utils::movementIndex];
            this->position = Utils::MoveTowards(this->position, targetPosition, abs(this->speed));

            if (this->position == targetPosition)
            {
                Utils::movementIndex = (Utils::movementIndex + 1) % (Utils::GetBoxPositionsLength());
            }
        }
        break;
    }

    glutPostRedisplay();
}

// Method Name: Render
// Description: Draws the model based on its settings
// author: Juan Alejandro Rodriguez Morais
// return: void
void GameObject::Render()
{
    glUseProgram(this->shaderProgram);

    glm::mat4 model, view, projection;
    model = glm::translate(model, this->position);

    model = glm::translate(model, vec3(0.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(this->rotation.x), vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(this->rotation.y), vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(this->rotation.z), vec3(0.0, 0.0, 1.0));
    model = glm::translate(model, vec3(0.0, 0.0, 0.0));

    model = glm::scale(model, this->scale);

    view = this->camera->GetViewMatrix();
    projection = this->camera->GetProjectionMatrix();

    // Get their uniform location
    GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");

    // Pass them to the shaders
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    GLint objColorLoc = glGetUniformLocation(this->shaderProgram, "colour");
    glUniform3f(objColorLoc, this->colour.x, this->colour.y, this->colour.z);

    GLuint cameraPosLoc = glGetUniformLocation(this->shaderProgram, "viewPosition");
    glUniform3f(cameraPosLoc, camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

    glBindVertexArray(this->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Method Name: SetStartPosition
// Description: Sets the start position of the object
// author: Juan Alejandro Rodriguez Morais
// param _position: The desired position
// return: void
void GameObject::SetStartPosition(vec3 _position)
{
    this->startPosition = _position;
}

// Method Name: SetColour
// Description: Sets the colour of the object (ALPHA values)
// author: Juan Alejandro Rodriguez Morais
// param _colour: The desired color
// return: void
void GameObject::SetColour(vec3 _colour)
{
    this->colour = _colour;
}

// Method Name: SetSpeed
// Description: Sets the speed of the object
// author: Juan Alejandro Rodriguez Morais
// param _speed: The desired speed
// return: void
void GameObject::SetSpeed(float _speed)
{
    this->speed = _speed;
}

// Method Name: SetMovementType
// Description: Sets the movement type and direction accordingly
// author: Juan Alejandro Rodriguez Morais
// param _type: The type of movement
// return: void
void GameObject::SetMovementType(MovementType _type)
{
    this->movementType = _type;
}

// Method Name: GetStartPosition
// Description: Returns the colour of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
vec3 GameObject::GetStartPosition() const
{
    return this->startPosition;
}

// Method Name: GetModelType
// Description: Returns the model type of the object
// author: Juan Alejandro Rodriguez Morais
// return: ModelType
ModelType GameObject::GetModelType() const
{
    return this->modelType;
}

// Method Name: GetMovementType
// Description: Returns the movement type of the object
// author: Juan Alejandro Rodriguez Morais
// return: MovementType
MovementType GameObject::GetMovementType() const
{
    return this->movementType;
}

// Method Name: GetColour
// Description: Returns the colour of the object
// author: Juan Alejandro Rodriguez Morais
// return: glm::vec3
vec3 GameObject::GetColour() const
{
    return this->colour;
}

// Method Name: GetSpeed
// Description: Returns the colour of the object
// author: Juan Alejandro Rodriguez Morais
// return: float
float GameObject::GetSpeed() const
{
    return this->speed;
}