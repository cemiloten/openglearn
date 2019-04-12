#version 330 core
layout (location = 0) in vec3 pos_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 texcoord_in;

out vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(pos_in, 1.0);

    texcoord = texcoord_in;
}
