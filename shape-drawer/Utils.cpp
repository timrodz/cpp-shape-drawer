#include "Utils.h"


glm::vec3 Utils::RGBtoAlpha(int r, int g, int b)
{
    return glm::vec3((float) r / 255, (float) g / 255, (float) b / 255);
}

glm::vec3 Utils::MoveTowards(glm::vec3 _currentPosition, glm::vec3 _targetPosition, float _maxDistanceDelta)
{
    glm::vec3 a = _targetPosition - _currentPosition;
    float magnitude = glm::length(a); // Length of vector (http://glm.g-truc.net/0.9.8/api/a00148.html#ga18d45e3d4c7705e67ccfabd99e521604)
    
    if (magnitude <= _maxDistanceDelta || magnitude == 0.0f)
    {
        return _targetPosition;
    }
    
    return (_currentPosition + a / magnitude * _maxDistanceDelta);
}

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

void Utils::SetSquareData(std::vector<VertexFormat>& vertices, std::vector<GLuint>& indices)
{
    std::vector<VertexFormat> Vertices;

    Vertices.push_back(VertexFormat(Position(-1.0, 1.0, 0.0), TexCoord(-1.0, 1.0), Normal(0.0f, 0.0f, 1.0))); // Top-left
    Vertices.push_back(VertexFormat(Position(1.0, 1.0, 0.0), TexCoord(1.0, 1.0), Normal(0.0f, 0.0f, 1.0))); // Top-right
    Vertices.push_back(VertexFormat(Position(1.0, -1.0, 0.0), TexCoord(1.0, -1.0), Normal(0.0f, 0.0f, 1.0))); // Bottom-right
    Vertices.push_back(VertexFormat(Position(-1.0f, -1.0, 0.0), TexCoord(-1.0, -1.0), Normal(0.0f, 0.0f, 1.0))); // Bottom-left

    std::vector<GLuint> Indices;

    Indices.push_back(0); Indices.push_back(1); Indices.push_back(2);
    Indices.push_back(0); Indices.push_back(2); Indices.push_back(3);

    vertices.clear(); indices.clear();
    vertices = Vertices;
    indices = Indices;
}

void Utils::SetCubeData(std::vector<VertexFormat>& vertices, std::vector<GLuint>& indices)
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

    vertices.clear(); indices.clear();
    vertices = Vertices;
    indices = Indices;
}

void Utils::SetHexagonData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices)
{
    std::vector<VertexFormat> Vertices;
    
    // TODO: Test this loop
    // for (int i = 0; i < 6; ++i)
    // {
    //     float y = sin(i/6.0*2*3.14);
    //     float x = cos(i/6.0*2*3.14);
    // }
    
    // TODO: Maybe divide them by 2?
    Vertices.push_back(VertexFormat(Position(-1.0, 2.0, 0.0), TexCoord(1.0, 1.0), Normal(0.0f, 0.0f, 1.0))); // Top-left
    Vertices.push_back(VertexFormat(Position(1.0, 2.0, 0.0), TexCoord(1.0, 1.0), Normal(0.0f, 0.0f, 1.0))); // Top-right
    Vertices.push_back(VertexFormat(Position(-1.0, -2.0, 0.0), TexCoord(-1.0, 1.0), Normal(0.0f, 0.0f, 1.0))); // Bottom-left
    Vertices.push_back(VertexFormat(Position(1.0, -2.0, 0.0), TexCoord(1.0, 1.0), Normal(0.0f, 0.0f, 1.0))); // Bottom-right
    Vertices.push_back(VertexFormat(Position(-2.0, 0.0, 0.0), TexCoord(-1.0, -1.0), Normal(0.0f, 0.0f, 1.0))); // Mid-left
    Vertices.push_back(VertexFormat(Position(2.0, 0.0, 0.0), TexCoord(1.0, -1.0), Normal(0.0f, 0.0f, 1.0))); // Mid-right
}

void Utils::SetSphereData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices)
{
    std::vector<VertexFormat> Vertices;

    std::vector<GLuint> Indices;

    double latitudeBands = 30;
    double longitudeBands = 30;
    double radius = 1.0f;

    for (double latNumber = 0; latNumber <= latitudeBands; latNumber++)
    {
        double theta = latNumber * 3.14 / latitudeBands;
        double sinTheta = sin(theta);
        double cosTheta = cos(theta);

        for (double longNumber = 0; longNumber <= longitudeBands; longNumber++)
        {
            double phi = longNumber * 2 * 3.14 / longitudeBands;
            double sinPhi = sin(phi);
            double cosPhi = cos(phi);

            VertexFormat vs;

            vs.texCoord.u = 1 - (longNumber / longitudeBands); // u
            vs.texCoord.v = 1 - (latNumber / latitudeBands);   // v

            vs.normal.x = cosPhi * sinTheta;   // x
            vs.normal.y = cosTheta;            // y
            vs.normal.z = 1;   // z

            vs.pos.x = radius * vs.normal.x;
            vs.pos.y = radius * vs.normal.y;
            vs.pos.z = radius * vs.normal.z;

            Vertices.push_back(vs);
        }
    }

    for (GLuint latNumber = 0; latNumber < latitudeBands; latNumber++)
    {
        for (GLuint longNumber = 0; longNumber < longitudeBands; longNumber++)
        {
            GLuint first = (latNumber * (longitudeBands + 1)) + longNumber;
            GLuint second = first + longitudeBands + 1;

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