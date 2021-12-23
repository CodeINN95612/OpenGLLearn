#version 450 core
layout (location = 0) in vec3 iPos;

uniform vec4 uColor;
uniform vec3 uOffset;

out vec4 fColor;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
   gl_Position = vec4(iPos + uOffset, 1.0f);
   float posx = map(iPos.x, -1.0f, 1.0f, 0.0f, 1.0f);
   float posy = map(iPos.y, -1.0f, 1.0f, 0.0f, 1.0f);
   vec3 pos = vec3(posx, posy, 0.5f);
   fColor = vec4(pos + uOffset, 1.0f);
};