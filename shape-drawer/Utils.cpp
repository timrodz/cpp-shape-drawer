//
//  File Name: Utils.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Handles global utilities that are commonly used in the program
//

#include "Utils.h"

#include <algorithm>
#include <string>

/* Static variable initialisations */
int Utils::movementIndex = 0;

glm::vec3 Utils::BoxPositions[] = {
    glm::vec3(1, 0, 0),
    glm::vec3(1, -1, 0),
    glm::vec3(0, -1, 0),
    glm::vec3(0, 0, 0)
};

// Method Name: GetBoxPositionsLength
// Description: Returns the length of the BoxPositions array
// author: Juan Alejandro Rodriguez Morais
// return: int
int Utils::GetBoxPositionsLength()
{
    return (sizeof(BoxPositions) / sizeof(BoxPositions[0]));
}

// Method Name: RGBtoAlpha
// Description: Creates an Alpha colour (0-1) based off an RGB value
// author: Juan Alejandro Rodriguez Morais
// param _r: The red colour channel
// param _g: The green colour channel
// param _b: The blue colour channel
// return: glm::vec3
glm::vec3 Utils::RGBtoAlpha(float _r, float _g, float _b)
{
    return glm::vec3((float) _r / 255, (float) _g / 255, (float) _b / 255);
}

// Method Name: MoveTowards
// Description: Moves a vector towards a desired target in a given time
// author: Juan Alejandro Rodriguez Morais
// param _currentPosition: The current vector
// param _targetPosition: The target vector
// param _distance: The distance delta
// return: glm::vec3
glm::vec3 Utils::MoveTowards(glm::vec3 _currentPosition, glm::vec3 _targetPosition, float _distance)
{
    glm::vec3 vector = _targetPosition - _currentPosition;

    // Length of vector (http://glm.g-truc.net/0.9.8/api/a00148.html#ga18d45e3d4c7705e67ccfabd99e521604)
    float magnitude = glm::length(vector);

    if (magnitude <= _distance || magnitude == 0.0f)
    {
        return _targetPosition;
    }

    return (_currentPosition + vector / magnitude * _distance);
}

#pragma region DataFill

// Method Name: SetSquareData
// Description: Populates vertex format and index data for a square
// author: Juan Alejandro Rodriguez Morais
// param _vertices: The VertexFormat structure
// param _indices: The GLuint index structure
// return: void
void Utils::SetSquareData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices)
{
    std::vector<VertexFormat> Vertices;

    Vertices.push_back(VertexFormat(Position(-1.0, 1.0, 0.0), TexCoord(-1.0, 1.0), Normal(0.0f, 0.0f, 1.0))); // Top-left
    Vertices.push_back(VertexFormat(Position(1.0, 1.0, 0.0), TexCoord(1.0, 1.0), Normal(0.0f, 0.0f, 1.0))); // Top-right
    Vertices.push_back(VertexFormat(Position(1.0, -1.0, 0.0), TexCoord(1.0, -1.0), Normal(0.0f, 0.0f, 1.0))); // Bottom-right
    Vertices.push_back(VertexFormat(Position(-1.0f, -1.0, 0.0), TexCoord(-1.0, -1.0), Normal(0.0f, 0.0f, 1.0))); // Bottom-left

    std::vector<GLuint> Indices;

    Indices.push_back(0); Indices.push_back(1); Indices.push_back(2);
    Indices.push_back(0); Indices.push_back(2); Indices.push_back(3);

    _vertices.clear(); _indices.clear();
    _vertices = Vertices;
    _indices = Indices;
}

// Method Name: SetTriangleData
// Description: Populates vertex format and index data for a triangle
// author: Juan Alejandro Rodriguez Morais
// param _vertices: The VertexFormat structure
// param _indices: The GLuint index structure
// return: void
void Utils::SetTriangleData(std::vector<VertexFormat>& vertices, std::vector<GLuint>&indices)
{
    std::vector<VertexFormat> Vertices;

    Vertices.push_back(VertexFormat(Position(0.0f, 1.0f, 0.0f), TexCoord(1, 1), Normal(0.0f, 0.0f, 1.0))); // Top
    Vertices.push_back(VertexFormat(Position(1.0, 0.0, 0.0), TexCoord(0, 1), Normal(0.0f, 0.0f, 1.0))); // Right
    Vertices.push_back(VertexFormat(Position(-1.0, 0.0, 0.0), TexCoord(1, 0), Normal(0.0f, 0.0f, 1.0))); // Left

    std::vector<GLuint>Indices;

    Indices.push_back(0);
    Indices.push_back(1);
    Indices.push_back(2);

    vertices.clear(); indices.clear();

    vertices = Vertices;
    indices = Indices;
}

// Method Name: SetCircleData
// Description: Populates vertex format and index data for a circle
// author: Juan Alejandro Rodriguez Morais
// param _vertices: The VertexFormat structure
// param _indices: The GLuint index structure
// return: void
void Utils::SetCircleData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices)
{
    Utils::SetPolygonData(_vertices, _indices, 30);
}

// Method Name: SethexagonData
// Description: Populates vertex format and index data for a hexagon
// author: Juan Alejandro Rodriguez Morais
// param _vertices: The VertexFormat structure
// param _indices: The GLuint index structure
// return: void
void Utils::SetHexagonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices)
{
    Utils::SetPolygonData(_vertices, _indices, 6);
}

// Method Name: SetCubeData
// Description: Populates vertex format and index data for a cube
// author: Juan Alejandro Rodriguez Morais
// param _vertices: The VertexFormat structure
// param _indices: The GLuint index structure
// return: void
void Utils::SetCubeData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices)
{
    std::vector<VertexFormat> Vertices;

    //back
    Vertices.push_back(VertexFormat(Position(-1.0f, -1.0, -1.0), TexCoord(0.0, 1.0), Normal(0.0f, 0.0f, -1.0)));
    Vertices.push_back(VertexFormat(Position(1.0, -1.0, -1.0), TexCoord(0.0, 0.0), Normal(0.0f, 0.0f, -1.0)));
    Vertices.push_back(VertexFormat(Position(1.0, 1.0, -1.0), TexCoord(1.0, 0.0), Normal(0.0f, 0.0f, -1.0)));
    Vertices.push_back(VertexFormat(Position(-1.0, 1.0, -1.0), TexCoord(1.0, 1.0), Normal(0.0f, 0.0f, -1.0)));

    //front
    Vertices.push_back(VertexFormat(Position(-1.0f, -1.0f, 1.0f), TexCoord(1.0, 1.0), Normal(0.0f, 0.0f, 1.0)));
    Vertices.push_back(VertexFormat(Position(1.0f, -1.0f, 1.0f), TexCoord(0.0, 1.0), Normal(0.0f, 0.0f, 1.0)));
    Vertices.push_back(VertexFormat(Position(1.0f, 1.0f, 1.0f), TexCoord(0.0, 0.0), Normal(0.0f, 0.0f, 1.0)));
    Vertices.push_back(VertexFormat(Position(-1.0f, 1.0f, 1.0f), TexCoord(1.0, 0.0), Normal(0.0f, 0.0f, 1.0)));

    //left
    Vertices.push_back(VertexFormat(Position(-1.0, 1.0, 1.0), TexCoord(0.0, 0.0), Normal(-1.0f, 0.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(-1.0, 1.0, -1.0), TexCoord(1.0, 0.0), Normal(-1.0f, 0.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(-1.0, -1.0, -1.0), TexCoord(1.0, 1.0), Normal(-1.0f, 0.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(-1.0f, -1.0, 1.0), TexCoord(0.0, 1.0), Normal(-1.0f, 0.0f, 0.0)));

    //right
    Vertices.push_back(VertexFormat(Position(1.0, 1.0, 1.0), TexCoord(1.0, 0.0), Normal(1.0f, 0.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(1.0, 1.0, -1.0), TexCoord(0.0, 0.0), Normal(1.0f, 0.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(1.0f, -1.0, -1.0), TexCoord(0.0, 1.0), Normal(1.0f, 0.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(1.0, -1.0, 1.0), TexCoord(1.0, 1.0), Normal(1.0f, 0.0f, 0.0)));

    //bottom
    Vertices.push_back(VertexFormat(Position(-1.0f, -1.0, -1.0), TexCoord(1.0, 1.0), Normal(0.0f, -1.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(1.0, -1.0, -1.0), TexCoord(0.0, 1.0), Normal(0.0f, -1.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(1.0, -1.0, 1.0), TexCoord(0.0, 0.0), Normal(0.0f, -1.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(-1.0, -1.0, 1.0), TexCoord(1.0, 0.0), Normal(0.0f, -1.0f, 0.0)));

    //top
    Vertices.push_back(VertexFormat(Position(-1.0f, 1.0f, -1.0f), TexCoord(0.0, 1.0), Normal(0.0f, 1.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(1.0f, 1.0f, -1.0f), TexCoord(1.0, 1.0), Normal(0.0f, 1.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(1.0f, 1.0f, 1.0f), TexCoord(1.0, 0.0), Normal(0.0f, 1.0f, 0.0)));
    Vertices.push_back(VertexFormat(Position(-1.0f, 1.0f, 1.0f), TexCoord(0.0, 0.0), Normal(0.0f, 1.0f, 0.0)));

    std::vector<GLuint> Indices;

    Indices.push_back(0); Indices.push_back(1); Indices.push_back(2);
    Indices.push_back(2); Indices.push_back(3); Indices.push_back(0);

    Indices.push_back(4); Indices.push_back(5); Indices.push_back(6);
    Indices.push_back(6); Indices.push_back(7); Indices.push_back(4);

    Indices.push_back(8); Indices.push_back(9); Indices.push_back(10);
    Indices.push_back(10); Indices.push_back(11); Indices.push_back(8);

    Indices.push_back(12); Indices.push_back(13); Indices.push_back(14);
    Indices.push_back(12); Indices.push_back(14); Indices.push_back(15);

    Indices.push_back(16); Indices.push_back(17); Indices.push_back(18);
    Indices.push_back(18); Indices.push_back(19); Indices.push_back(16);

    Indices.push_back(20); Indices.push_back(21); Indices.push_back(22);
    Indices.push_back(22); Indices.push_back(23); Indices.push_back(20);

    _vertices.clear(); _indices.clear();
    _vertices = Vertices;
    _indices = Indices;
}

// Method Name: SetPentagonData
// Description: Populates vertex format and index data for a pentagon
// author: Juan Alejandro Rodriguez Morais
// param _vertices: The VertexFormat structure
// param _indices: The GLuint index structure
// return: void
void Utils::SetPentagonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices)
{
    Utils::SetPolygonData(_vertices, _indices, 5);
}

// Method Name: SetHeptagonData
// Description: Populates vertex format and index data for a heptagon
// author: Juan Alejandro Rodriguez Morais
// param _vertices: The VertexFormat structure
// param _indices: The GLuint index structure
// return: void
void Utils::SetHeptagonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices)
{
    Utils::SetPolygonData(_vertices, _indices, 7);
}

// Method Name: SetPolygonData
// Description: Fills up a polygon using the Triangle Fan method.
// author: Juan Rodriguez
// param _vertices: GameModel vertices (VertexFormat)
// param _indices: GameModel indices (GLuint)
// param _polygonCount: The amount of polygons to be used for the object
// return: void
void Utils::SetPolygonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices, int _polygonCount)
{
    std::vector<VertexFormat> Vertices;

    // Add the origin
    Vertices.push_back(VertexFormat(Position(0.0, 0.0, 0.0), TexCoord(1.0, 1.0), Normal(0.0f, 0.0f, 1.0)));

    int vertexCount = _polygonCount + 2;
    float radius = 1.0f;
    float center_x = 0.0f;
    float center_y = 0.0f;

    // Create a buffer for vertex data
    int index = 0;

    // Outer vertices of the circle
    int outerVertexCount = vertexCount - 1;

    for (int i = 0; i < outerVertexCount; ++i)
    {
        float percent = (i / (float) (outerVertexCount - 1));
        float rad = percent * 2.0f * PI;

        //Vertex position
        float outer_x = center_x + radius * cos(rad);
        float outer_y = center_y + radius * sin(rad);

        VertexFormat vs;
        vs.pos.x = outer_x;
        vs.pos.y = outer_y;
        vs.pos.z = 0;

        Vertices.push_back(vs);
    }

    std::vector<GLuint> Indices;

    for (GLuint latNumber = 0; latNumber < vertexCount; latNumber++)
    {
        for (GLuint longNumber = 0; longNumber < vertexCount; longNumber++)
        {
            GLuint first = (latNumber * (vertexCount + 1)) + longNumber;
            GLuint second = first + vertexCount + 1;

            Indices.push_back(first);
            Indices.push_back(second);
            Indices.push_back(first + 1);

            Indices.push_back(second);
            Indices.push_back(second + 1);
            Indices.push_back(first + 1);
        }
    }

    _vertices.clear(); _indices.clear();
    _vertices = Vertices;
    _indices = Indices;
}
#pragma endregion

// Method Name: ToLower
// Description: Converts a string to lowercase
// This is useful for comparing strings
// author: Juan Alejandro Rodriguez Morais
// param _string: The string to convert
// return: void
void Utils::ToLower(std::string& _string)
{
    std::transform(_string.begin(), _string.end(), _string.begin(), ::tolower);
}

// Method Name: GetModelTypeFromString
// Description: Returns a model type based on a given string
// author: Juan Alejandro Rodriguez Morais
// param _string: The string that contains the text
// return: ModelType
ModelType Utils::GetModelTypeFromString(std::string _string)
{
    ToLower(_string);

    if (_string == "square") return ModelType::Square;
    else if (_string == "triangle") return ModelType::Triangle;
    else if (_string == "circle") return ModelType::Circle;
    else if (_string == "hexagon") return ModelType::Hexagon;
    else if (_string == "cube") return ModelType::Cube;
    else if (_string == "pentagon") return ModelType::Pentagon;
    else if (_string == "heptagon") return ModelType::Heptagon;

    return ModelType::Triangle;
}

// Method Name: GetMovementTypeFromString
// Description: Returns a movement type based on a given string
// author: Juan Alejandro Rodriguez Morais
// param _string: The string that contains the text
// return: MovementType
MovementType Utils::GetMovementTypeFromString(std::string _string)
{
    ToLower(_string);

    if (_string == "idle") return MovementType::Idle;
    else if (_string == "updown") return MovementType::UpDown;
    else if (_string == "leftright") return MovementType::LeftRight;
    else if (_string == "circular") return MovementType::Circular;
    else if (_string == "box") return MovementType::Box;

    return MovementType::Idle;
}

// Method Name: GetVector3FromString
// Description: Returns a vector3 based on a given string
// It must follow this format: (x, y, z)
// author: Juan Alejandro Rodriguez Morais
// param _string: The string that contains the text
// return: glm::vec3
glm::vec3 Utils::GetVector3FromString(std::string _string)
{
    float x, y, z;

    std::size_t first = _string.find("(");
    std::size_t second = _string.find(",");
    std::string tempStr = _string.substr(first + 1, second - 1);
    x = std::stof(tempStr);

    _string = _string.substr(tempStr.length() + 2, _string.length() - 1);

    first = _string.find(" ");
    second = _string.find(",");
    tempStr = _string.substr((first != std::string::npos) ? first + 1 : 0, second - 1);
    y = std::stof(tempStr);

    _string = _string.substr(tempStr.length() + 2, _string.length() - 1);

    first = _string.find(" ");
    second = _string.find(")");
    tempStr = _string.substr((first != std::string::npos) ? first + 1 : 0, second - 1);
    z = std::stof(tempStr);

    return glm::vec3(x, y, z);
}
