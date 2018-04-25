//
//  File Name: main.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Handles the main logic of the program
//

#include <iostream>

#include "Utils.h"
#include "GameScene.h"
#include "GameModel.h"
#include "Camera.h"
#include "Cubemap.h"
#include "INIParser.h"

/* Avoid repetition of common code */
using std::cout;
using std::endl;
using glm::vec3;

/* Global variables (Scope is this file) */
unsigned char KeyCode[255];
bool anyKeyDown;
ShaderLoader g_ShaderLoader;
GLuint g_shaderProgram;

/* Functions */
void Render();
void Update();
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void LoadModelsFromFile();

// Method Name: main
// Description: The main program entry loop
// author: Juan Alejandro Rodriguez Morais
// return: int
int main(int argc, char **argv)
{
    // Initialise Glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2);
    glutInitWindowSize(Utils::WIDTH, Utils::HEIGHT);
    glutCreateWindow("PikPok Competency Test - Juan Rodriguez");
    
    // Initialise OpenGL
    glClearDepth(1.0f);                                 // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                            // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                             // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                            // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    
    // Initialise Glew
    glewInit();

    // Initialise the box movement index (Utils)
    Utils::movementIndex = 0;

    // Initialise the global camera at (0, 0, 10)
    Camera* g_Camera = new Camera(vec3(0, 0, 10), 45.0f, Utils::WIDTH, Utils::HEIGHT);

    // Create the Cubemap
    GLuint cubemapProgram = g_ShaderLoader.CreateProgram("shaders/skybox.vs", "shaders/skybox.fs");
    Cubemap* g_Skybox = new Cubemap(cubemapProgram, g_Camera);

    // Create default shader program, most objects will use it.
    g_shaderProgram = g_ShaderLoader.CreateProgram("shaders/unlit.vs", "shaders/unlit.fs");

    // Get the scene instance. We will add a camera and models to it
    GameScene::GetInstance().SetCamera(g_Camera);
    GameScene::GetInstance().SetCubemap(g_Skybox);
    
    // Load default scene
    //gs.CreateDefaultScene(g_shaderProgram);
    
    // Load models from external file
    //LoadModelsFromFile();

    // Main loop functions
    glutDisplayFunc(Render);
    glutKeyboardFunc(KeyDown);
    glutKeyboardUpFunc(KeyUp);
    glutIdleFunc(Update);
    
    // Run the main Glut loop
    glutMainLoop();

    return (EXIT_SUCCESS);
}

// Method Name: Render
// Description: Handles the main rendering logic
// author: Juan Alejandro Rodriguez Morais
// return: void
void Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GameScene::GetInstance().Render();

    glutSwapBuffers();
}

// Method Name: Update
// Description: Handles the main update logic
// author: Juan Alejandro Rodriguez Morais
// return: void
void Update()
{
    GLfloat deltaTime = (GLfloat) glutGet(GLUT_ELAPSED_TIME);
    deltaTime *= 0.001f;

    GameScene::GetInstance().Update(deltaTime);
    
    // Handle key inputs (Menu)
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
            LoadModelsFromFile();
            anyKeyDown = true;
            cout << "Load external files" << endl;
        }
        if (KeyCode[(unsigned char)'3'] == KeyState::Pressed)
        {
            GameScene::GetInstance().ClearScene();
            GameScene::GetInstance().CreateDefaultScene(g_shaderProgram);
            LoadModelsFromFile();
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

// Method Name: KeyDown
// Description: Handles key state when a key is pressed
// author: Juan Alejandro Rodriguez Morais
// return: void
void KeyDown(unsigned char key, int x, int y)
{
    KeyCode[key] = KeyState::Pressed;
    cout << "Key pressed: " << key << endl;
}

// Method Name: KeyUp
// Description: Handles key state when a key is released
// author: Juan Alejandro Rodriguez Morais
// return: void
void KeyUp(unsigned char key, int x, int y)
{
    KeyCode[key] = KeyState::Released;
    anyKeyDown = false;
    cout << "Key Released: " << key << endl;
}

// Method Name: LoadModelsFromFile
// Description: Loads the shapes.ini file and creates models based on the settings input there
// author: Juan Alejandro Rodriguez Morais
// return: void
void LoadModelsFromFile()
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
        GameScene::GetInstance().CreateModel(mod, mov, g_shaderProgram, texture, colour, scale, position, rotation, speed);
    }

}