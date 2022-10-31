#version 450 core

layout (location = 0) out vec4 fColor;

in vec3 squareColor;
in vec2 texCoord;

uniform sampler2D image_texture;
uniform sampler2D watermark_texture;

void main() {
    fColor = mix(texture(image_texture, texCoord), texture(watermark_texture, texCoord), 0.4);
}