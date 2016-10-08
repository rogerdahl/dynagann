#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

out vec3 interFragPos;
out vec3 interNormal;

uniform mat4 uniModel;
uniform mat4 uniView;
uniform mat4 uniProj;

void main()
{
    gl_Position = uniProj * uniView * uniModel * vec4(inPosition, 1.0f);
    interFragPos = vec3(uniModel * vec4(inPosition, 1.0f));
    interNormal = mat3(transpose(inverse(uniModel))) * inNormal;
}
