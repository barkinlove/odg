#version 330

layout(location = 0) in vec3 pos;
layout(location = 3) in vec3 vertexColor;

// layout(location = 1) in vec3 normals;
// layout(location = 2) in vec2 texture;

uniform float gScale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;

// const vec4 colors[4] = vec4[4](vec4(1, 0, 0, 1), vec4(0, 1, 0, 1), vec4(0, 0, 1, 1), vec4(1, 1, 1, 1));
// const vec4 red[3] = vec4[3](vec4(1, 0, 0, 1), vec4(0, 0, 0, 1), vec4(0, 0, 0, 1));

void main()
{
  gl_Position = projection * view * model * vec4(pos, 1.0);
  color = vec4(vertexColor, 1.0);
}
