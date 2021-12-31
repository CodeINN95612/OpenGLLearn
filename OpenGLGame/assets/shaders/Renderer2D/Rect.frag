#version 450 core

in vec2 fTextureCoords;

uniform sampler2D uTexture;
uniform vec4 uColor;

out vec4 oColor;

void main()
{
   oColor = texture(uTexture, fTextureCoords) * uColor;
}