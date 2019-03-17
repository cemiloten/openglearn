#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 v_color_in;

out vec3 v_color;

uniform float h_offset;

void main()
{
    gl_Position = vec4(pos.x + h_offset, pos.y, pos.z, 1.0);
    // v_color = v_color_in;
    v_color = pos;
}
