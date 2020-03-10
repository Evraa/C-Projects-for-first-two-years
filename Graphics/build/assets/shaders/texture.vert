#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 normal;

uniform mat4 M;
uniform mat4 M_it;

uniform mat4 VP;
uniform mat4 V;
uniform vec3 cam_pos;

out Interpolators {
    vec3 world;
    vec3 view;
    vec3 normal;
} vs_out;
//FOG
out float visibility;
const float density = 0.007;
const float gradient = 1.5;
//vec4 posToCam ;

out vec2 vUV;
void main()
{
    vUV = uv;
    vec4 world = M * vec4(position, 1.0f);
    vs_out.world = world.xyz;
    vs_out.view = cam_pos - world.xyz;
    vs_out.normal = normalize(M_it * vec4(normal, 0.0f)).xyz;
  
    //FOG calculations
    vec3 vue = cam_pos - world.xyz;
    vec4 posToCam = V * world;
    float distance = length(posToCam.xyz);
    float var = distance*density;
	visibility = pow(var,gradient);
	visibility = exp(-visibility);
	visibility = clamp(visibility,0.0,1.0);

    gl_Position = VP * world;
}
