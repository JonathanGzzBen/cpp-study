#version 450 core

layout (location = 0) out vec4 fColor;

in vec3 squareColor;
in vec2 texCoord;

uniform sampler2D myTexture;

void main() {
    fColor = texture(myTexture, texCoord);
}