#version 330 core

uniform vec3 lightColor;

out vec4 fragmentColor;

void main() {
    fragmentColor = vec4(lightColor, 1.0f);
}
