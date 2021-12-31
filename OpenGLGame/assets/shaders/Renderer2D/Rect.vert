#version 450 core
layout (location = 0) in vec2 iPos;
layout (location = 1) in vec2 iTextureCoords;

uniform mat4 uMVP;
out vec2 fTextureCoords;

void main()
{
   gl_Position = uMVP * vec4(iPos, 0.0f, 1.0f);
   fTextureCoords = iTextureCoords;
};