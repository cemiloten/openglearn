#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 v_color_in;
layout (location = 2) in vec2 uv_coords_in;

out vec3 v_color;
out vec2 uv_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    v_color = v_color_in;
    uv_coords = uv_coords_in;
}
