//
//  File Name: main.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
// 
//

#include <iostream>

#include "Utils.h"
#include "GameModel.h"
#include "Camera.h"
#include "Cubemap.h"

using std::cout;
using glm::vec3;

// Classes
ShaderLoader g_ShaderLoader;
Camera* g_Camera;
//Light* light;
GameModel* g_Square;
GameModel* g_Triangle;
GameModel* g_Circle;
GameModel* g_Hexagon;

Cubemap* g_Skybox;

unsigned char KeyCode[255];

void Render();
void Update();
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void AnimateModel(GameModel* _model, vec3 _moveDirection);

int main(int argc, char **argv)
{
    // Initialise Glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2);
    glutInitWindowSize(Utils::WIDTH, Utils::HEIGHT);
    glutCreateWindow("PikPok Competency Test - Juan Rodriguez");

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);               // Set background color to black and opaque
    glClearDepth(1.0f);                                 // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                            // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                             // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                            // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    glewInit();

    // -- Object creation
    g_Camera = new Camera(vec3(0, 0, 8), Utils::WIDTH, Utils::HEIGHT);

    GLuint squareProgram = g_ShaderLoader.CreateProgram("shaders/unlit.vs", "shaders/unlit.fs");
    g_Square = new GameModel(ModelType::Square, g_Camera);
	g_Square->SetTexture("textures/triangle.jpg");
    g_Square->SetProgram(squareProgram);
    g_Square->SetMovementType(MovementType::LeftRight);
    g_Square->SetColor(Utils::RGBtoAlpha(227, 181, 5));
    g_Square->SetPosition(vec3(-4, 0, 0));
    g_Square->SetSpeed(0.05f);

    GLuint triangleProgram = g_ShaderLoader.CreateProgram("shaders/unlit.vs", "shaders/unlit.fs");
    g_Triangle = new GameModel(ModelType::Triangle, g_Camera);
    g_Triangle->SetProgram(triangleProgram);
    g_Triangle->SetMovementType(MovementType::UpDown);
    g_Triangle->SetColor(Utils::RGBtoAlpha(219, 80, 74));
    g_Triangle->SetPosition(vec3(4, 0, 0));
    g_Triangle->SetSpeed(0.05f);

    GLuint circleProgram = g_ShaderLoader.CreateProgram("shaders/unlit.vs", "shaders/unlit.fs");
    g_Circle = new GameModel(ModelType::Circle, g_Camera);
    g_Circle->SetProgram(circleProgram);
    g_Circle->SetMovementType(MovementType::Box);
    g_Circle->SetColor(Utils::RGBtoAlpha(86, 163, 166));
    g_Circle->SetPosition(vec3(0, -2, 0));
    g_Circle->SetSpeed(0.05f);

	GLuint hexagonProgram = g_ShaderLoader.CreateProgram("shaders/unlit.vs", "shaders/unlit.fs");
	g_Hexagon = new GameModel(ModelType::Hexagon, g_Camera);
	g_Hexagon->SetProgram(hexagonProgram);
	g_Hexagon->SetMovementType(MovementType::Circular);
	g_Hexagon->SetColor(Utils::RGBtoAlpha(51, 153, 51));
	g_Hexagon->SetPosition(vec3(0, 2, 0));
	g_Hexagon->SetSpeed(3);

    // Skybox
    GLuint cubemapProgram = g_ShaderLoader.CreateProgram("shaders/skybox.vs", "shaders/skybox.fs");
    g_Skybox = new Cubemap(cubemapProgram, g_Camera);

    glutDisplayFunc(Render);
    glutKeyboardFunc(KeyDown);
    glutKeyboardUpFunc(KeyUp);
    glutIdleFunc(Update);

    glutMainLoop();

    return (EXIT_SUCCESS);
}

void Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Models to render
    //g_Skybox->Render();
    g_Square->Render();
    g_Triangle->Render();
    g_Circle->Render();
	g_Hexagon->Render();

    glutSwapBuffers();
}

void Update()
{
    GLfloat deltaTime = (GLfloat) glutGet(GLUT_ELAPSED_TIME);
    deltaTime *= 0.001f;

    // Update the models
    g_Square->Update(deltaTime);
    g_Triangle->Update(deltaTime);
    g_Circle->Update(deltaTime);
	g_Hexagon->Update(deltaTime);

    //LerpAtoB<GameModel>(g_Triangle, vec3(1, 1, 1), vec3(2, 1, 1));
}

void KeyDown(unsigned char key, int x, int y)
{

    KeyCode[key] = KeyState::Pressed;
    cout << "Key pressed: " << key << "\n";

}

void KeyUp(unsigned char key, int x, int y)
{

    KeyCode[key] = KeyState::Released;
    cout << "Key Released: " << key << "\n";

}

// Function AnimateModel
// Animates the model by moving it in a few spaces in the given direction
// author : Juan Rodriguez
// param _model : The game model that will be animated
// param _moveDirection : The direction of the movement
void AnimateModel(GameModel* _model, vec3 _moveDirection)
{



}