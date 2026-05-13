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

// For normal mapping:
uniform sampler2D normalMap;
uniform bool useNormalMap;

void main() {
  vec3 n = normalize(worldSpaceNormal);
  // https://learnopengl.com/Advanced-Lighting/Normal-Mapping
  if (useNormalMap) {
    // calculate triangle's edges (change in vertex coordinates)
    vec3 edge1  = dFdx(worldSpacePosition);
    vec3 edge2  = dFdy(worldSpacePosition);
    // calculate change in UV coordinates
    vec2 deltaUV1  = dFdx(shaderUV);
    vec2 deltaUV2  = dFdy(shaderUV);

    // TBN matrix
    // T is tangent, determining the U direction in world space
    // B is bitangent, determining the V direction in world space. This is gotten by cross product of n and T
    // N is just the normal
    // We use this so the normal mapping is correct regardless of object's rotation
    vec3 T = normalize(edge1 * deltaUV2.t - edge2 * deltaUV1.t);
    vec3 B = -normalize(cross(n, T));
    mat3 TBN = mat3(T, B, n);

    vec3 mapNormal = texture(normalMap, shaderUV).rgb * 2.0 - 1.0;
    n = normalize(TBN * mapNormal);
  }

  vec3 lightPosition = lightPos;
  vec3 l = normalize(lightPosition - worldSpacePosition);
  
  float diffuse = max(dot(n, l), 0.0);
  vec3 diffuseColor = diffuse * lightColor;
  vec3 ambient = 0.75f * vec3(0.22f, 0.08f, 0.35f);

  vec3 viewDir = normalize(cameraPos - worldSpacePosition);
  vec3 reflectDir = reflect(-l, n);
  float specularLight = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  vec3 specular = specularStrength * specularLight * lightColor;
  vec3 lighting = ambient + diffuseColor + specular;

  vec4 texColor = texture(top_texture, shaderUV);
  fragmentColor = texColor * vec4(lighting * objectColor, 1.0f);
}