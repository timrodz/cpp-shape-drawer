//
//  File Name: Utils.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file containing:
// 1. External library definitions
// 2. Internal library/file definitions
// 3. Global defines
// 4. Enums
// 5. Vertex Format structs
// 6. Utilities class
//

#pragma once

/* External libraries */
// GLEW
#include <glew\glew.h>

// GLUT
#include <freeglut\freeglut.h>

// SOIL - TODO: remove
#include <soil\SOIL.h>

// MATH
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/* Internal libraries/files */
#include <vector>
#include "ShaderLoader.h"

/* Constants */
#define PI 3.14159265358979323846264338327950288f // Pi

/* Enums */
#pragma region Enums
enum KeyState
{
    Released = 0,
    Pressed = 1
};

enum ModelType
{
    Square = 0,
    Triangle = 1,
    Circle = 2,
    Hexagon = 3,
    Cube = 4,
    Pentagon = 5,
    Heptagon = 6
};

enum MovementType
{
    Idle = 0,
    UpDown,
    LeftRight,
    Circular,
    Box
};
#pragma endregion

/* Vertex Formats */
#pragma region VertexFormat
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
#pragma endregion

/* Utilities class */
class Utils
{
public:
    const static int WIDTH = 1280;
    const static int HEIGHT = 720;

    const static int VERTICAL_LIMIT = 2;
    const static int HORIZONTAL_LIMIT = 2;
    const static int CIRCULAR_RADIUS = 1;
    static int movementIndex;
    static glm::vec3 BoxPositions[];
    static int GetBoxPositionLength();

    static glm::vec3 RGBtoAlpha(float _r, float _g, float _b);
    static glm::vec3 MoveTowards(glm::vec3 _currentPosition, glm::vec3 _targetPosition, float _maxDistanceDelta);

    static void SetSquareData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
    static void SetTriangleData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
    static void SetCircleData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
    static void SetHexagonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
    static void SetCubeData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
    static void SetPentagonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
    static void SetHeptagonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);

    static void ToLower(std::string& _string);

    static ModelType GetModelType(std::string _string);
    static MovementType GetMovementType(std::string _string);
    static glm::vec3 GetVector3(std::string _string);

private:
    static void SetPolygonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>&_indices, int _polygonCount);
};

/// File header
//
//  File Name: 
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  
//

/// Method header
// Method Name: 
// Description: 
// author: Juan Alejandro Rodriguez Morais
// param: 
// return: 