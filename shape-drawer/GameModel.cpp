#include "GameModel.h"
#include "Camera.h"

GameModel::GameModel(ModelType _modelType, Camera* _camera)
{
    camera = _camera;

    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    position = glm::vec3(0.0, 0.0, 0.0);
    color = glm::vec3(1.0f, 1.0f, 1.0f);

    speed = 0.0f;
    rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    m_MovementType = MovementType::Idle;

    //glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_FALSE);//if enabled, disables writing to depth
    //glDepthFunc(GL_LESS);//passes if the fragment depth value is less than stored depth value

    switch (_modelType)
    {
        case Triangle: Utils::SetTriangleData(vertices, indices); break;
        case Square: Utils::SetSquareData(vertices, indices); break;
        case Hexagon: Utils::SetHexagonData(vertices, indices); break;
        case Cube: Utils::SetCubeData(vertices, indices); break;
        case Circle: Utils::SetSphereData(vertices, indices); break;
    }

    for (auto item : vertices)
    {
        //printf("position: %f, %f, %f \n", item.pos.x, item.pos.y, item.pos.z);
    }

    for (auto item : indices)
    {
        //printf("index: %d, %d, %d \n", item.x, item.y, item.z);
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

    //this->SetTexture(texFileName);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*) 0);

    // Texture Coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*) (offsetof(VertexFormat, VertexFormat::texCoord)));

    // Normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*) (offsetof(VertexFormat, VertexFormat::normal)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

GameModel::~GameModel()
{
    //this->camera = nullptr;
    //delete this->camera;
}

void GameModel::Update(GLfloat time)
{
    //model = glm::rotate(model,glm::radians(45.0f) * time, glm::vec3(0.0, 1.0, 0.0f));
    //model = glm::translate(model, position);
    switch (m_MovementType)
    {
        case (MovementType::UpDown):
        {
            if (position.y < Utils::VERTICAL_LIMIT)
            {
                position += glm::vec3(0, 1, 0) * 0.05f;
            }
            else if (position.y > -Utils::VERTICAL_LIMIT)
            {
                position -= glm::vec3(0, 1, 0) * 0.05f;
            }
        }
        break;
    }
    glutPostRedisplay();
}


void GameModel::Render()
{
    glUseProgram(this->program);

    glColor3f(1, 1, 0);

    glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glUniform1i(glGetUniformLocation(program, "Texture"), 0);

    glm::mat4 model, view, projection;
    model = glm::translate(model, position);

    model = glm::translate(model, glm::vec3(0.0f * this->scale.x, 0.0f * scale.y, 0.0f));
    model = glm::rotate(model, glm::radians(angle.x), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0.0, 0.0, 1.0));
    model = glm::translate(model, glm::vec3(-0.0f * scale.x, -0.0f * scale.y, 0.0f));

    model = glm::scale(model, scale);

    //glm::mat4 vp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
    //GLint vpLoc = glGetUniformLocation(program, "vp");
    //glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    // Transformation matrices

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
    glUniform3f(objColorLoc, color.x, color.y, color.z);

    GLuint cameraPosLoc = glGetUniformLocation(program, "viewPosition");
    glUniform3f(cameraPosLoc, camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

    /*GLuint lightPosLoc = glGetUniformLocation(program, "lightPosition");
    glUniform3f(lightPosLoc, this->light->GetPosition().x, this->light->GetPosition().y, this->light->GetPosition().z);

    GLuint lightColorLoc = glGetUniformLocation(program, "lightColor");
    glUniform3f(lightColorLoc, this->light->GetColor().x, this->light->GetColor().y, this->light->GetColor().z);*/

    /*GLuint specularStrengthLoc = glGetUniformLocation(program, "specularStrength");
    glUniform1f(specularStrengthLoc, specularStrength);

    GLuint ambientStrengthLoc = glGetUniformLocation(program, "ambientStrength");
    glUniform1f(ambientStrengthLoc, ambientStrength);*/

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

//movement
//void GameModel::MoveForward()
//{
//	position -= glm::vec3(0.0f, 0.0f, 1.0f) * speed;
//}
//
//void GameModel::MoveBackward()
//{
//	position += glm::vec3(0.0f, 0.0f, 1.0f) * speed;
//}
//
//void GameModel::MoveLeft()
//{
//	position -= glm::vec3(1.0f, 0.0f, 0.0f) * speed;
//}
//
//void GameModel::MoveRight()
//{
//	position += glm::vec3(1.0f, 0.0f, 0.0f) * speed;
//}
//
//void GameModel::MoveUp()
//{
//	position += glm::vec3(0.0f, 1.0f, 0.0f) * speed;
//}
//
//void GameModel::MoveDown()
//{
//	position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed;
//}

void GameModel::Rotate(glm::vec3 axis)
{
    this->angle.x += axis.x * speed * 20;
    this->angle.y += axis.y * speed * 20;
    this->angle.z += axis.z * speed * 20;
}

//void GameModel::SetTexture(std::string  texFileName)
//{
//	////** load texture
//	//glGenTextures(1, &texture);
//	//glBindTexture(GL_TEXTURE_2D, texture);
//
//	//// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//// Set texture filtering parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	////** loadImage and create texture
//	//// Load image, create texture and generate mipmaps
//	//int width, height;
//	//unsigned char* image = SOIL_load_image(texFileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	//glGenerateMipmap(GL_TEXTURE_2D);
//	//SOIL_free_image_data(image);
//	//glBindTexture(GL_TEXTURE_2D, 0);
//
//	//printf("fileName %s \n", texFileName.c_str());
//
//	//bIsTextureSet = true;
//}

// setters and getters

void GameModel::SetScale(glm::vec3 _scale)
{
    this->scale = _scale;
}

//void GameModel::SetRotation(glm::vec3 angle)
//{
//	this->angle = angle;
//}
//
//void GameModel::SetRotationAxis(glm::vec3 rotationAxis)
//{
//	this->rotationAxis = rotationAxis;
//}

void GameModel::SetPosition(glm::vec3 _position)
{
    this->position = _position;
}

void GameModel::SetColor(glm::vec3 _color)
{
    this->color = _color;
}

void GameModel::SetCamera(Camera * camera)
{}

void GameModel::SetSpeed(float _speed)
{
    this->speed = _speed;
}

void GameModel::SetProgram(GLuint program)
{
    this->program = program;
}

//void GameModel::SetSpecularStrength(float strength)
//{
//	specularStrength = strength;
//}

void GameModel::SetMovementType(MovementType _type)
{
    m_MovementType = _type;
}

glm::vec3 GameModel::GetPosition()
{
    return position;
}

glm::vec3 GameModel::GetColor()
{
    return this->color;
}

void GameModel::Move()
{

}

glm::vec3 GameModel::GetScale()
{
    return this->scale;
}

glm::vec3 GameModel::GetRotation()
{
    return this->angle;
}

//glm::vec3 GameModel::GetRotationAxis()
//{
//	return rotationAxis;
//}