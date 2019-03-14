#version 330 core

in vec3 vertexColor;

out vec4 outColor;

void main() {
    outColor = vec4(vertexColor, 1.0);
    // outColor = vec4(1.0, 0.5, 0.2, 1.0);
}
