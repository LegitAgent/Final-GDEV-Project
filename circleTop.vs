#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in vec3 vertexNormal; 

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

out vec3 worldSpacePosition;
out vec3 worldSpaceNormal;
out vec3 objectColor;
out vec2 shaderUV;

void main() {
    worldSpacePosition = (modelMatrix * vec4(vertexPosition, 1.0f)).xyz;
    worldSpaceNormal = (normalMatrix * vec4(vertexNormal, 0.0f)).xyz;
    objectColor = vertexColor;
    gl_Position = projectionMatrix * vec4(worldSpacePosition, 1.0f);
    shaderUV = vertexUV;
}