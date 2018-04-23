#pragma once

#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <soil\SOIL.h>

// Math
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ShaderLoader.h"

#include <vector>

// Keyboard callbacks
enum KeyState {
	Pressed,
	Released
};

/*
Model Type
*/

enum ModelType {

	Triangle = 0,
	Square = 1,
	Hexagon = 2,
	Circle = 3

};


/*
Vertex Format
*/

struct Position {

	float x, y, z;

	Position(float _x, float _y, float _z) {

		x = _x; y = _y; z = _z;
	}

	Position() {}

};

struct TexCoord {

	float u, v;

	TexCoord(float _u, float _v) {
		u = _u; v = _v;
	}

	TexCoord() {}

};

struct Normals {

	float x, y, z;

	Normals(float _x, float _y, float _z) {

		x = _x; y = _y; z = _z;
	}

	Normals() {}

};

struct VertexFormat {

	Position pos;
	TexCoord texCoord;
	Normals normal;

	VertexFormat(Position _pos, TexCoord _texCoord, Normals _normal) {

		pos = _pos;
		texCoord = _texCoord;
		normal = _normal;

	}

	VertexFormat() {}

};

struct IndexFormat {

	int x; int y; int z;

	IndexFormat(int _x, int _y, int _z) {

		x = _x; y = _y; z = _z;
	}

};


class Utils {

public:

	const static int WIDTH = 1280;
	const static int HEIGHT = 720;

	static glm::vec3 alphaConversionFromRGB(int r, int g, int b);
	static void setTriData(std::vector<VertexFormat>& vertices, std::vector<GLuint>&indices);
	static void setQuadData(std::vector<VertexFormat>& vertices, std::vector<GLuint>&indices);
	static void setCubeData(std::vector<VertexFormat>& vertices, std::vector<GLuint>&indices);
	static void setSphereData(std::vector<VertexFormat>& vertices, std::vector<GLuint>&indices);

};





