#version 330 core

// Ouput data
layout(location = 0) out float fragmentdepth;
//layout(location = 0) out vec4 fragmentdepth;

void main(){
    // Not really needed, OpenGL does it anyway
    fragmentdepth = gl_FragCoord.z;
//    fragmentdepth = vec4(.5,1,1,1);
}
