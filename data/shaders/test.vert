#version 330 core
layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 texcoord_in;

out vec2 texcoord;
out vec3 normal;
out vec3 world_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(pos_in, 1.0);
  world_pos = vec3(model * vec4(pos_in, 1.0));

  texcoord = texcoord_in;
  normal = normal_in;
}
