#version 330 core

in vec3 objectColor;
in vec2 shaderUV;

uniform sampler2D sunTexture;
uniform vec3 lightColor;
uniform float time;

out vec4 fragmentColor;

void main() {
    vec4 texColor = texture(sunTexture, shaderUV + vec2(time * 0.01, time * 0.01));
    fragmentColor = vec4(texColor.rgb * lightColor, texColor.a);
}
