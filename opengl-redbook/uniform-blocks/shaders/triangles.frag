#version 450 core

//uniform vec4 color;
uniform color {
    float red;
    float green;
    float blue;
};

layout (location = 0) out vec4 fColor;

void main() {
    fColor = vec4(red, green, blue, 1.0);
}