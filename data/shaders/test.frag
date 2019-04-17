#version 330 core

out vec4 frag_color;

in vec2 texcoord;
in vec3 normal;
in vec3 frag_view_pos;
in vec3 light_view_pos;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

uniform vec3 light_color;

void main() {
  vec3 unit_normal = normalize(normal);

  vec3 frag_to_light = normalize(light_view_pos - frag_view_pos);
  float light_intensity = max(dot(unit_normal, frag_to_light), 0.0);

  vec3 frag_to_eye = normalize(-frag_view_pos);
  vec3 reflection_dir = reflect(-frag_to_light, unit_normal);
  float spec = pow(max(dot(frag_to_eye, reflection_dir), 0.0), 32);
  frag_color = vec4(spec);
  return;
//   vec3 s = specular_strength * spec * light_color;

  float _ambient = 0.0;
  vec3 color = (_ambient + spec * 0.5) * light_color * diffuse;
  // vec3 color = (_ambient + light_intensity + spec * 0.5) * light_color * diffuse;
  frag_color = vec4(color, 1.0f);
}
