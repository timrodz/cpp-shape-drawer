#version 430 core

out vec4 color;

uniform vec3 colour;

void main() 
{
	color = vec4(colour, 1.0f);
}