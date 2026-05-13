#version 330 core

layout (location = 0) in vec3 vertexPosition;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main() {
    gl_Position = projectionMatrix * modelMatrix * vec4(vertexPosition, 1.0f);
}
