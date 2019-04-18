#version 330 core

layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 texcoord_in;

out vec2 texcoord;
out vec3 normal;
out vec3 frag_view_pos;
out vec3 light_view_pos;

uniform vec3 light_world_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(pos_in, 1.0);
  frag_view_pos = vec3(view * model * vec4(pos_in, 1.0));
  light_view_pos = vec3(view * vec4(light_world_pos, 1.0));

  normal = mat3(transpose(inverse(view * model))) * normal_in;
  texcoord = texcoord_in;
}
