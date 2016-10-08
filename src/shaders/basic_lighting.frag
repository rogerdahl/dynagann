#version 330 core

out vec4 outColor;

in vec3 interFragPos;  
in vec3 interNormal;  
  
uniform vec3 uniLightPos; 
//uniform vec3 uniViewPos;
uniform vec3 uniObjectColor;

vec3 lightColor = vec3(1, 1, 1);

vec3 uniViewPos = vec3(0,8,10);

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 normal = normalize(interNormal);
    vec3 lightDir = normalize(uniLightPos - interFragPos);
  	// If the dot product N·L is negative, the light source is on the “wrong” side of the surface and we set
  	// the reflection to 0.
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * 0.3;
    
    // Specular
//    float specularStrength = 1.0f;
//    vec3 viewDir = normalize(uniViewPos - interFragPos);
//    vec3 reflectDir = reflect(lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = specularStrength * spec * lightColor;

    vec3 incidenceVector = -surfaceToLight; //a unit vector
    vec3 reflectionVector = reflect(incidenceVector, normal); //also a unit vector
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePosition); //also a unit vector
    float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
    float specularCoefficient = pow(cosAngle, materialShininess);

    vec3 specularComponent = specularCoefficient * materialSpecularColor * light.intensities;

    vec3 result = (ambient + diffuse + specular) * uniObjectColor;

    outColor = vec4(result, 1.0);
}
