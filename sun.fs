#version 330 core

in vec3 objectColor;
in vec2 shaderUV;

uniform sampler2D sunTexture;
uniform vec3 lightColor;

out vec4 fragmentColor;

void main() {
    vec4 texColor = texture(sunTexture, shaderUV * 0.1);
    fragmentColor = vec4(texColor.rgb * lightColor, texColor.a);
}
