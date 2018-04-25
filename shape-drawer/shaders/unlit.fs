#version 430 core

in vec2 TexCoord;
in vec3 OutNormVec;
in vec3 OutFragPosition;

out vec4 color;

uniform sampler2D Texture;

uniform vec3 objectColor;

void main() 
{
	// Color only
	color = vec4(objectColor, 1.0f);

	// Color + Texture (Not working at the moment)
    color = texture(Texture, TexCoord) * vec4(objectColor,  1.0f);
}