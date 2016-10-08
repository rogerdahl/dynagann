#version 330

uniform mat4 uniView;
uniform mat4 uniProj;
uniform mat4 uniModel;
uniform mat4 depthBiasMVP;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

out vec3 interFragPos;
out vec3 interNormal;
out vec4 shadowCoord;

void main() {
    interNormal = inNormal;
    interFragPos = inPosition;
    gl_Position = uniProj * uniView * uniModel * vec4(inPosition, 1.0f);
    // Same, but with the light's view matrix
    shadowCoord = depthBiasMVP * vec4(inPosition, 1);
}
