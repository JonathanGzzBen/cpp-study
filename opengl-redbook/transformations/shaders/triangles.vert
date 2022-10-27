#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 mTransform;

out vec3 squareColor;
out vec2 texCoord;

void main() {
    gl_Position = mTransform * vPosition;
    squareColor = vColor;
    texCoord = vTexCoord;
}