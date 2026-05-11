#version 330 core

in vec3 objectColor;
in vec2 shaderUV;

uniform sampler2D background_texture;

out vec4 fragmentColor;

void main() {
    vec4 texColor = texture(background_texture, shaderUV);
    fragmentColor = vec4(texColor.rgb * objectColor, texColor.a);
}
