#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 vCubePositions[2];

uniform mat4 mTransform;
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

out vec3 squareColor;
out vec2 texCoord;

void main() {
    gl_Position = mProjection * mView * mModel * vCubePositions[gl_InstanceID] * mTransform * vPosition;
    texCoord = vTexCoord;
}