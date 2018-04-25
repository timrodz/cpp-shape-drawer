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
#include "INIParser.h"

using std::cout;
using std::endl;
using glm::vec3;

// Classes
ShaderLoader g_ShaderLoader;
GLuint g_shaderProgram;
Camera* g_Camera;
Cubemap* g_Skybox;

void Render();
void Update();
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void LoadModelsFromFile(GLuint _shaderProgram);
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
    g_Camera = new Camera(vec3(0, 0, 10), 45.0f, Utils::WIDTH, Utils::HEIGHT);

    // Skybox
    GLuint cubemapProgram = g_ShaderLoader.CreateProgram("shaders/skybox.vs", "shaders/skybox.fs");
    g_Skybox = new Cubemap(cubemapProgram, g_Camera);

    // Default shader program, most objects will use it.
    g_shaderProgram = g_ShaderLoader.CreateProgram("shaders/unlit.vs", "shaders/unlit.fs");

    // Get the scene instance. We will add a camera and models to it
    GameScene& gs = GameScene::GetInstance();
    gs.SetCamera(g_Camera);

    //gs.CreateDefaultScene(g_shaderProgram);
    //LoadModelsFromFile(g_shaderProgram);

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
        if (KeyCode[(unsigned char)'1'] == KeyState::Pressed)
        {
            GameScene::GetInstance().ClearScene();
            GameScene::GetInstance().CreateDefaultScene(g_shaderProgram);
            anyKeyDown = true;
            cout << "Load Default Scene" << endl;
        }
        if (KeyCode[(unsigned char)'2'] == KeyState::Pressed)
        {
            GameScene::GetInstance().ClearScene();
            LoadModelsFromFile(g_shaderProgram);
            anyKeyDown = true;
            cout << "Load external files" << endl;
        }
        if (KeyCode[(unsigned char)'3'] == KeyState::Pressed)
        {
            GameScene::GetInstance().ClearScene();
            GameScene::GetInstance().CreateDefaultScene(g_shaderProgram);
            LoadModelsFromFile(g_shaderProgram);
            anyKeyDown = true;
            cout << "Load default scene with external files" << endl;
        }
        if (KeyCode[(unsigned char)'r'] == KeyState::Pressed || KeyCode[(unsigned char)'R'] == KeyState::Pressed)
        {
            GameScene::GetInstance().ClearScene();
            anyKeyDown = true;
            cout << "Scene cleared" << endl;
        }
    }
}

void KeyDown(unsigned char key, int x, int y)
{
    KeyCode[key] = KeyState::Pressed;
    cout << "Key pressed: " << key << endl;
}

void KeyUp(unsigned char key, int x, int y)
{
    KeyCode[key] = KeyState::Released;
    anyKeyDown = false;
    cout << "Key Released: " << key << endl;
}

void LoadModelsFromFile(GLuint _shaderProgram)
{
    INIParser parser;
    if (!parser.LoadIniFile("shapes"))
    {
        cout << "ERROR: shapes.ini is empty" << endl;
        return;
    }

    std::string line = "";

    // Populate shapes
    for (int i = 1; i <= parser.GetSectionCount(); ++i)
    {
        std::string s = "shape" + std::to_string(i);
        const char* shape = s.c_str();

        // Model Type
        parser.GetStringValue(shape, "ModelType", line);
        ModelType mod = Utils::GetModelType(line);

        // Movement Type
        parser.GetStringValue(shape, "MovementType", line);
        MovementType mov = Utils::GetMovementType(line);

        // Movement Type
        parser.GetStringValue(shape, "Texture", line);
        const char* texture = line.c_str();

        // Colour
        parser.GetStringValue(shape, "Colour", line);
        glm::vec3 colour = Utils::GetVector3(line);
        colour = Utils::RGBtoAlpha(colour.r, colour.g, colour.b);

        // Position
        parser.GetStringValue(shape, "Scale", line);
        glm::vec3 scale = Utils::GetVector3(line);

        // Position
        parser.GetStringValue(shape, "Position", line);
        glm::vec3 position = Utils::GetVector3(line);

        // Rotation
        parser.GetStringValue(shape, "Rotation", line);
        glm::vec3 rotation = Utils::GetVector3(line);

        // Speed
        float speed = 0.0f;
        parser.GetFloatValue(shape, "Speed", speed);

        // Build the model
        GameScene::GetInstance().CreateModel(mod, mov, _shaderProgram, texture, colour, scale, position, rotation, speed);
    }

}