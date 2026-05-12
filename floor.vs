#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in vec3 vertexNormal;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform sampler2D noiseMap;
uniform float floorScroll;
uniform float heightScale;

out vec3 worldSpacePosition;
out vec3 worldSpaceNormal;
out vec3 objectColor;
out vec2 shaderUV;

void main() {
    vec2 chunkUV = vertexUV / vec2(35.553f, 80.0f); // get it on a per chunk basis (66.666 x 150 texture images per segment)
    float height = texture(noiseMap, chunkUV).r; // get the red value of the noisemap
    float centeredHeight = height * 2.0f - 1.0f; // convert from 0 to 1 to -1 to 1
    
    // displace by some scale
    vec3 displacedPosition = vertexPosition + vertexNormal * centeredHeight * heightScale;

    worldSpacePosition = (modelMatrix * vec4(displacedPosition, 1.0f)).xyz;
    worldSpaceNormal = (normalMatrix * vec4(vertexNormal, 0.0f)).xyz;
    objectColor = vertexColor;
    shaderUV = vertexUV;
    gl_Position = projectionMatrix * vec4(worldSpacePosition, 1.0f);
}
