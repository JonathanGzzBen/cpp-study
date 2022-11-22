#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec4 vCubePosition;

uniform mat4 mTransform;
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

out vec3 squareColor;
out vec2 texCoord;

void main() {
    mat4 mViewModel = mView * mModel;
    gl_Position = mProjection * mViewModel * vec4(vPosition + vCubePosition);
    texCoord = vTexCoord;
}