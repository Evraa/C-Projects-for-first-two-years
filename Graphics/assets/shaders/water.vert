#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 uv;

uniform mat4 MVP;

out vec2 vUV;
out vec4 clipSpace;

void main()
{
    vUV = uv;
    clipSpace = MVP * vec4(position, 1.0f);
    gl_Position = clipSpace;
    
 }