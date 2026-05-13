#version 330 core

in vec3 objectColor;
in vec2 shaderUV;

uniform sampler2D background_texture;
uniform float backgroundScroll;

out vec4 fragmentColor;

void main() {
    vec2 scrollBG = shaderUV + vec2(0.0f, backgroundScroll);
    vec4 texColor = texture(background_texture, scrollBG);
    fragmentColor = vec4(texColor.rgb * objectColor, texColor.a);
}
