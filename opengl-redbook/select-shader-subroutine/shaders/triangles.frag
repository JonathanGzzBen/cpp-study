#version 450 core

uniform vec4 color;
layout (location = 0) out vec4 fColor;

subroutine vec4 ColorEffect(vec4);

subroutine (ColorEffect) vec4 invertColor(vec4 color) {
    return vec4(1.0 - color.r, 1.0 - color.g, 1.0 - color.b, color.a);
}

subroutine (ColorEffect) vec4 noColorEffect(vec4 color) {
    return color;
}

subroutine uniform ColorEffect colorEffect;

void main() {
    fColor = colorEffect(color);
}