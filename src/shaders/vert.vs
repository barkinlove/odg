#version 330

layout(location = 0) in vec3 pos;
uniform float gScale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;

const vec4 colors[4] = vec4[4](vec4(1, 0, 0, 1), vec4(0, 1, 0, 1), vec4(0, 0, 1, 1), vec4(1, 1, 1, 1));
const vec4 red[3] = vec4[3](vec4(1, 0, 0, 1), vec4(0, 0, 0, 1), vec4(0, 0, 0, 1));

void main() {
  gl_Position = projection * view * model * vec4(pos, 1.0);
  color = colors[gl_VertexID];
}
