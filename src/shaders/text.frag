#version 330 core

uniform sampler2D s;
in vec2 f_uv;
out vec3 color;

void main(void) {
    color = texelFetch(s, ivec2(f_uv), 0).rgb;
}
