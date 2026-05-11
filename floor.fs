#version 330 core

in vec3 worldSpacePosition;
in vec3 worldSpaceNormal;
in vec3 objectColor;
in vec2 shaderUV; // floor coords

uniform sampler2D floor_texture;
uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float shininess;
uniform float specularStrength;
uniform float floorScroll;

out vec4 fragmentColor;

// https://docs.gl/

void main() {
    vec2 movingUV = shaderUV + vec2(0.0f, floorScroll); // parallax movement, move only y coord for up down
    vec2 cell = fract(movingUV); // fract == get the fract area i.e. 3.25 == .25, for scaling uv no matter how big

    float gridLine = step(cell.x, 0.035f) + step(cell.y, 0.035f); // return 1 if cell.x < 0.035f, (0.035f is basically the thickness of the line)
    gridLine = clamp(gridLine, 0.0f, 1.0f); // can be 2 so clamp to 0 to 1, 0 = no line, 1 = line

    vec3 baseColor = mix(vec3(0.05f, 0.02f, 0.12f), vec3(0.00f, 0.95f, 1.00f), gridLine); // mix two colors, read opengl docs

    // copy paste from texturedLit.fs
    vec3 lightDir = normalize(lightPos - worldSpacePosition);
    vec3 surfaceNorm = normalize(worldSpaceNormal);
    float diffuse = max(dot(surfaceNorm, lightDir), 0.0f);
    vec3 diffuseColor = diffuse * lightColor;
    vec3 ambient = 0.85f * vec3(0.28f, 0.08f, 0.45f);

    vec3 viewDir = normalize(cameraPos - worldSpacePosition);
    vec3 reflectDir = reflect(-lightDir, surfaceNorm);
    float specularLight = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
    vec3 specular = specularStrength * 0.08f * specularLight * lightColor;
    vec3 lighting = ambient + diffuseColor + specular;

    vec4 texColor = texture(floor_texture, movingUV);
    vec3 litFloor = texColor.rgb * baseColor * objectColor * lighting;
    vec3 gridGlow = vec3(0.2f, 0.8f, 1.0f) * gridLine * 1.5f;

    fragmentColor = vec4(litFloor + gridGlow, texColor.a);
}
