#version 330 core

out vec4 frag_color;

in vec2 texcoords;
in vec3 normal;
in vec3 frag_view_pos;
in vec3 light_view_pos;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct LightColor {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Material material;
uniform LightColor light_color;

void main() {
  vec3 unit_normal = normalize(normal);

  vec3 diffuse_sample = vec3(texture(material.diffuse, texcoords));
  vec3 specular_sample = vec3(texture(material.specular, texcoords));

  vec3 ambient = light_color.ambient * diffuse_sample;

  vec3 frag_to_light = normalize(light_view_pos - frag_view_pos);
  float diff = max(dot(unit_normal, frag_to_light), 0.0);
  vec3 diffuse = light_color.diffuse * (diff * diffuse_sample);

  vec3 reflection_dir = reflect(-frag_to_light, unit_normal);
  vec3 frag_to_eye = normalize(-frag_view_pos);
  float spec = pow(max(dot(frag_to_eye, reflection_dir), 0.0), 32);
  vec3 specular = light_color.specular * (spec * specular_sample);

  vec3 color = (ambient + diffuse + specular);
  frag_color = vec4(color, 1.0f);
}
