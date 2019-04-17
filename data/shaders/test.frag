#version 330 core

out vec4 frag_color;

in vec2 texcoord;
in vec3 normal;
in vec3 frag_pos;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 eye_pos;

void main() {
  frag_color = vec4(1.0);

  float ambient_strength = 0.1;
  vec3 a = ambient_strength * light_color;
  frag_color.xyz = ambient;
  return;

  vec3 norm = normalize(normal);
  vec3 frag_to_light = normalize(light_pos - frag_pos);

  float light_intensity = max(dot(norm, frag_to_light), 0.0);
  vec3 l = light_intensity * light_color;

  vec3 frag_to_eye = normalize(eye_pos - frag_pos);
  vec3 reflection_dir = reflect(-frag_to_light, norm);

  float specular_strength = 0.5;
  float spec = pow(max(dot(frag_to_eye, reflection_dir), 0.0), 32);
  vec3 s = specular_strength * spec * light_color;

  vec3 result = (a + l + s) * diffuse;
  frag_color = vec4(result, 1.0f);
}
