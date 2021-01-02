#version 300 es

precision mediump float;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;

out vec2 vFragTexture;

//uniform float uTime;
uniform mat3 uModelMatrix;

mat3 rotate(float a){
  return mat3(vec3(cos(radians(a)),sin(radians(a)),0),vec3(-sin(radians(a)),cos(radians(a)),0),vec3(0,0,1));
}

mat3 scale(float x, float y){
  return mat3(vec3(x,0,0),vec3(0,y,0),vec3(0,0,1));
}

void main() {

    //vFragColor = uColor;
    vFragTexture = aVertexTexture;
    //vFragPosition = aVertexPosition;
    //mat3 M = scale(0.5,0.5) * rotate(uTime);
    //gl_Position = vec4((M * vec3(aVertexPosition,1)).xy, 0, 1);
    gl_Position = vec4((uModelMatrix * vec3(aVertexPosition,1)).xy, 0, 1);
}
