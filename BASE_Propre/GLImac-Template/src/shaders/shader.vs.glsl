#version 300 es

precision mediump float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 uWMatrix;		// World Matrix
uniform mat4 uPMatrix;		// Projection Matrix
uniform mat4 uNMatrix;		// Normal Matrix

out vec3 vPosition_vs;	// Positions in View space
out vec3 vNormal_vs;		// Normals
out vec2 vTexCoords;		// Texture coords

void main(){
	// Homogeneous coordinates
	vec4 vertexPosition = vec4(position, 1);
	vec4 vertexNormal   = vec4(normal, 0);

	vPosition_vs = vec3(uWMatrix * vertexPosition);
	vNormal_vs   = vec3(uNMatrix * vertexNormal);
	vTexCoords   = texCoords;

	// Projected positions
  gl_Position = uPMatrix * vertexPosition;
}
