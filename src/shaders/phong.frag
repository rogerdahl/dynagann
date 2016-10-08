#version 330

uniform mat4 uniModel;
uniform vec3 uniCameraPos;
uniform vec4 uniSurfaceColor;
uniform vec3 uniLightPos;

in vec3 interFragPos;
in vec3 interNormal;
in vec4 shadowCoord;

uniform sampler2D shadowMap;

out vec4 finalColor;

// Config.

vec3 lightColor = vec3(1, 1, 1);
float lightAttenuation = 0.006;
float lightAmbientCoefficient = 0.008;

float materialShininess = 4.0f;
vec3 materialSpecularColor = vec3(1,1,1);


void main() {
//    finalColor = texture(shadowMap, ShadowCoord.xy );
//    finalColor = vec4(visibility, visibility, visibility, 1.0);
//    finalColor = vec4(.1, texture(shadowMap, ShadowCoord.xy).z, 0, 1.0);
//    return;

    vec3 normal = normalize(transpose(inverse(mat3(uniModel))) * interNormal);
    vec3 surfacePos = vec3(uniModel * vec4(interFragPos, 1));
    vec3 surfaceToLight = normalize(uniLightPos - surfacePos);
    vec3 surfaceToCamera = normalize(uniCameraPos - surfacePos);

    // Shadows
    // http://learnopengl.com/#!Advanced-Lighting/Shadows/Shadow-Mapping
    // Need both this bias and biasMatrix in main.cpp in phong.vert. Investigate...
    float bias = max(0.05 * (1.0 - dot(normal, uniLightPos)), 0.004);
    bool shadow = false;
    if (texture(shadowMap, shadowCoord.xy).x + bias < shadowCoord.z) {
        shadow = true;
    }

    // Ambient
    vec3 ambient = lightAmbientCoefficient * uniSurfaceColor.rgb * lightColor;

    // Diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * uniSurfaceColor.rgb * lightColor;

    // Specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0) {
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
    }
    vec3 specular = specularCoefficient * materialSpecularColor * lightColor;

    // Attenuation
    float distanceToLight = length(uniLightPos - surfacePos);
    float attenuation = 1.0 / (1.0 + lightAttenuation * pow(distanceToLight, 2));

    // Color, before gamma correction
    // There's no specular light in shadows.
    vec3 linearColor;
    if (shadow) {
        linearColor = (ambient + attenuation * diffuse) * 0.5;
    }
    else {
        linearColor = (ambient + attenuation * (diffuse + specular));
    }

    // Color, after gamma correction
    vec3 gamma = vec3(1.0 / 2.2);
    finalColor = vec4(pow(linearColor, gamma), uniSurfaceColor.a);
//    finalColor = vec4(pow(linearColor, gamma), uniSurfaceColor.a);
}
