#version 330 core

in vec3 worldSpacePosition;
in vec3 worldSpaceNormal;
in vec3 objectColor;
in vec2 shaderUV;

uniform sampler2D top_texture;
uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float shininess;
uniform float specularStrength;
out vec4 fragmentColor;

void main() {
  vec3 lightPosition = lightPos;
  vec3 l = normalize(lightPosition - worldSpacePosition);
  vec3 n = normalize(worldSpaceNormal);
  float diffuse = max(dot(n, l), 0.0);
  vec3 diffuseColor = diffuse * lightColor;
  vec3 ambient = 0.5f * vec3(0.157f, 0.110f, 0.235f);

  vec3 viewDir = normalize(cameraPos - worldSpacePosition);
  vec3 reflectDir = reflect(-l, n);
  float specularLight = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  vec3 specular = specularStrength * specularLight * lightColor;
  vec3 lighting = ambient + diffuseColor + specular;

  vec4 texColor = texture(top_texture, shaderUV);
  fragmentColor = texColor * vec4(lighting * objectColor, 1.0f);
}