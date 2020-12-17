#version 300 es

precision mediump float;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;
uniform sampler2D uTextureNuages;

void main()
{
	vec4 couleursTerre  = texture(uTexture, vTexCoords) ;
	vec4 couleursNuages = texture(uTextureNuages, vTexCoords);
	fFragColor = couleursTerre.xyz + couleursNuages.xyz;
}
