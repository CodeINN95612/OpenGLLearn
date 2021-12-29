#version 450 core

layout (location = 0) in vec2 iPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec4 uColor;

out vec4 fColor;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(iPos, 0.0f, 1.0f);
	fColor = uColor;
}