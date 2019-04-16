#version 330 core

out vec4 frag_color;

in vec2 texcoord;
in vec3 normal;
in vec3 world_pos;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 light_color;
uniform vec3 light_pos;

void main() {
  float ambient_strength = 0.1;
  vec3 ambient = ambient_strength * light_color;

  vec3 norm = normalize(normal);
  vec3 light_direction = normalize(light_pos - world_pos);

  float light_intensity = max(dot(norm, light_direction), 0.0);
  vec3 light = light_intensity * light_color;

  vec3 result = (ambient + light) * diffuse;
  frag_color = vec4(result, 1.0f);
}
