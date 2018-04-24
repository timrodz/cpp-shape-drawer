#pragma once

/* External libraries */
// GLEW
#include <glew\glew.h>

// GLUT
#include <freeglut\freeglut.h>

// SOIL - TODO: remove
//#include <soil\SOIL.h>

// MATH
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/* Internal libraries/files */
#include <vector>

#include "ShaderLoader.h"

/* Constants */

/* Enums */
enum KeyState
{
    Pressed,
    Released
};

enum ModelType
{
    Square = 0,
    Triangle = 1,
    Circle = 2,
    Sphere = 3,
    Cube = 4,
    Hexagon = 7
};

enum MovementType
{
    Idle = 0,
    UpDown,
    LeftRight,
    Circular,
    Box
};

/* Vertex Format */
struct Position
{
    float x, y, z;

    Position(float _x, float _y, float _z)
    {
        x = _x; y = _y; z = _z;
    }

    Position() {}
};

struct TexCoord
{
    float u, v;

    TexCoord(float _u, float _v)
    {
        u = _u; v = _v;
    }

    TexCoord() {}
};

struct Normal
{
    float x, y, z;

    Normal(float _x, float _y, float _z)
    {
        x = _x; y = _y; z = _z;
    }

    Normal() {}
};

struct VertexFormat
{
    Position pos;
    TexCoord texCoord;
    Normal normal;

    VertexFormat(Position _pos, TexCoord _texCoord, Normal _normal)
    {
        pos = _pos;
        texCoord = _texCoord;
        normal = _normal;
    }

    VertexFormat() {}
};

struct IndexFormat
{
    int x, y, z;

    IndexFormat(int _x, int _y, int _z)
    {
        x = _x; y = _y; z = _z;
    }

    IndexFormat() {}
};


class Utils
{

public:
    const static int WIDTH = 1280;
    const static int HEIGHT = 720;

    const static int VERTICAL_LIMIT = 2;
    const static int HORIZONTAL_LIMIT = 2;
    const static int CIRCULAR_RADIUS = 1;
    const static glm::vec3 BOX_POSITIONS = {
        (1, 0, 0),
        (1, -1, 0),
        (0, -1, 0),
        (0, 0, 0)
    };
    static int movementIndex = 0;

    static glm::vec3 RGBtoAlpha(int _r, int _g, int _b);
    static glm::vec3 MoveTowards(glm::vec3 _currentPosition, glm::vec3 _targetPosition, float _maxDistanceDelta);
    
    static void SetSquareData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>&_indices);
    static void SetTriangleData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>&_indices);
    static void SetHexagonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>&_indices);
    static void SetCubeData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>&_indices);
    // TODO: Replace for circle
    static void SetSphereData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>&_indices);
};