#version 300 es

precision mediump float;

in vec2 vFragTexture;
//in vec3 vFragColor;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
    fFragColor = texture(uTexture,vFragTexture).xyz;
}
