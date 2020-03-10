#version 330 core

in vec2 vUV; //texture coordinats

uniform sampler2D reflect;
uniform sampler2D dudvMap;	
uniform float moveFactor;

out vec4 color;

const float waveStrenngth = 0.02;
void main()
{
  
	/*
    vec2 distortion1 = (texture(dudvMap,vec2 (vUV.x + moveFactor , vUV.y)).rg *2.0 - 1.0)*waveStrenngth;
   	vec2 distortion2 = (texture(dudvMap,vec2 (-vUV.x  , vUV.y+ moveFactor)).rg *2.0 - 1.0)*waveStrenngth;
    vec2 newUV2 =vUV + distortion1+distortion2 ;
*/
vec2 distortion1 = texture(dudvMap, vec2 (vUV.x + moveFactor,vUV.y)).rg *0.1;
distortion1 = vUV + vec2(distortion1.x,distortion1.y +moveFactor);
vec2 newUV2 =(texture(dudvMap,distortion1).rg *2.0 -1.0) *waveStrenngth;
    color = texture(reflect,newUV2);
    color = mix (color, vec4(0.390325f,0.1953125f,0,0.6f) ,0.2);
}