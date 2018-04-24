//
//  File Name: main.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
// 
//

#include <iostream>

#include "Utils.h"
#include "GameScene.h"
#include "GameModel.h"
#include "Camera.h"
#include "Cubemap.h"

using std::cout;
using glm::vec3;

// Classes
ShaderLoader g_ShaderLoader;
Camera* g_Camera;
Cubemap* g_Skybox;

void Render();
void Update();
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
unsigned char KeyCode[255];
bool anyKeyDown;

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

    // Initialise the box movement index (Utils)
    Utils::movementIndex = 0;

    // Initialise the global camera at (0, 0, 10)
    g_Camera = new Camera(vec3(0, 0, 10), Utils::WIDTH, Utils::HEIGHT);

    GLuint shaderProgram = g_ShaderLoader.CreateProgram("shaders/unlit.vs", "shaders/unlit.fs");

    // Get the scene instance. We will add a camera and models to it
    GameScene& gs = GameScene::GetInstance();
    gs.AddCamera(g_Camera);
    //gs.CreateDefaultScene(shaderProgram);

    gs.CreateModel(ModelType::Triangle, MovementType::LeftRight, shaderProgram, "", Utils::RGBtoAlpha(51, 153, 51), vec3(-4, 0, 0), vec3(0, 0, 0), 0.05f);
    gs.CreateModel(ModelType::Square, MovementType::UpDown, shaderProgram, "", Utils::RGBtoAlpha(227, 181, 5), vec3(4, 0, 0), vec3(0, 0, 0), 0.05f);
    gs.CreateModel(ModelType::Circle, MovementType::Box, shaderProgram, "", Utils::RGBtoAlpha(86, 163, 166), vec3(0, -2, 0), vec3(0, 0, 0), 0.05f);
    gs.CreateModel(ModelType::Hexagon, MovementType::Circular, shaderProgram, "", Utils::RGBtoAlpha(219, 80, 74), vec3(0, 2, 0), vec3(0, 0, 0), 3.0f);
    gs.CreateModel(ModelType::Pentagon, MovementType::Idle, shaderProgram, "", Utils::RGBtoAlpha(219, 80, 74), vec3(-4, -3, 0), vec3(0, 0, 0), 3.0f);

    // Skybox
    GLuint cubemapProgram = g_ShaderLoader.CreateProgram("shaders/skybox.vs", "shaders/skybox.fs");
    g_Skybox = new Cubemap(cubemapProgram, g_Camera);

    // Main loop functions
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

    g_Skybox->Render();
    GameScene::GetInstance().Render();

    glutSwapBuffers();
}

void Update()
{
    GLfloat deltaTime = (GLfloat) glutGet(GLUT_ELAPSED_TIME);
    deltaTime *= 0.001f;

    GameScene::GetInstance().Update(deltaTime);

    if (!anyKeyDown)
    {

        if (KeyCode[(unsigned char)'q'] == KeyState::Pressed || KeyCode[(unsigned char)'Q'] == KeyState::Pressed)
        {
            GameScene::GetInstance().ClearScene();
            anyKeyDown = true;
            cout << "Clear scene" << std::endl;
        }
        if (KeyCode[(unsigned char)'r'] == KeyState::Pressed || KeyCode[(unsigned char)'R'] == KeyState::Pressed)
        {
            GameScene::GetInstance().ReloadScene();
            anyKeyDown = true;
            cout << "Scene reloaded" << std::endl;
        }
    }
}

void KeyDown(unsigned char key, int x, int y)
{
    KeyCode[key] = KeyState::Pressed;
    cout << "Key pressed: " << key << "\n";
}

void KeyUp(unsigned char key, int x, int y)
{
    KeyCode[key] = KeyState::Released;
    anyKeyDown = false;
    cout << "Key Released: " << key << "\n";
}