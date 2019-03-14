#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vertexColorIn;

out vec3 vertexColorOut;

void main() {
    gl_Position = vec4(pos, 1.0);
    vertexColorOut = vec3(1.0, 0.5, 1.0);
}
