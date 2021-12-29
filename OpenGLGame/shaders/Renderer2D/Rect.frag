#version 450 core

in vec2 fTextureCoords;

uniform sampler2D uTexture;

out vec4 oColor;

void main()
{
   oColor = texture(uTexture, fTextureCoords);
}