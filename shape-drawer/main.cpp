//
//  File Name   : main.cpp
//  Author	   : Juan Alejandro Rodriguez Morais
//  Mail		   : timrodz@icloud.com
//
//  DESCRIPTION
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
GameModel* g_Triangle;
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

    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);               // Set background color to black and opaque
    glClearDepth(1.0f);                                 // Set background depth to farthest
    //glEnable(GL_DEPTH_TEST);                            // Enable depth testing for z-culling
    //glDepthFunc(GL_LEQUAL);                             // Set the type of depth-test
    //glShadeModel(GL_SMOOTH);                            // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    glewInit();

    //glewExperimental = true;

    // -- Object creation
    g_Camera = new Camera(vec3(0, 0, 8), Utils::WIDTH, Utils::HEIGHT);

    GLuint triangleProgram = g_ShaderLoader.CreateProgram("shaders/unlit.vs", "shaders/unlit.fs");
    g_Triangle = new GameModel(ModelType::Circle, g_Camera, MovementDirection::UpDown);
    g_Triangle->SetColor(Utils::RGBtoAlpha(66, 134, 244));
    g_Triangle->SetProgram(triangleProgram);
    g_Triangle->SetPosition(vec3(-3, -0.5f, 0));
    g_Triangle->SetSpeed(0.005f);

    // Skybox
    //GLuint cubemapProgram = shaderLoader.CreateProgram("shaders/skybox.vs", "shaders/skybox.fs");
    //skybox = new Cubemap(cubemapProgram, camera);

    // -- Object creation

    glutDisplayFunc(Render);
    glutKeyboardFunc(KeyDown);
    glutKeyboardUpFunc(KeyUp);
    glutIdleFunc(Update);

    glutMainLoop();

    return (EXIT_SUCCESS);

}

void Render()
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Models to render
    g_Triangle->Render();
    //skybox->Render();

    glutSwapBuffers();
}

void Update()
{
    GLfloat deltaTime = (GLfloat) glutGet(GLUT_ELAPSED_TIME);
    deltaTime *= 0.001f;

    // Update the models
    g_Triangle->Update(deltaTime);
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