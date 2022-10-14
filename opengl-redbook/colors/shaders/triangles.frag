#version 450 core

layout (location = 0) out vec4 fColor;

in vec3 squareColor;

void main() {
    fColor = vec4(squareColor, 1.0);
}