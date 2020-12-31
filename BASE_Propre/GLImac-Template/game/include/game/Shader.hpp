#pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <sstream>

#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include "Light.hpp"
#include "Light_Ambient.hpp"
#include "Light_Directional.hpp"
#include "Light_Point.hpp"

#include "utils.hpp"

namespace game
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		bool init(const char* vsFilename, const char* fsFilename);	// Create a shader program
		void use();																									// Use the shader program

		// Setters for the uniforms variables
		void setTextureLocation(unsigned int v);
		void setProjectionMatrix(const float* v);
		void setWorldMatrix(const float* v);
		void setNormalMatrix(const float* v);

		void setDiffuse(const glm::vec3 d);
		void setSpecular(const glm::vec3 s);
		void setShininess(const float s);
		void setLampON(int v);
		int getLampON();

		void setLights(const std::vector<Light*> lights, const glm::mat4* ViewMatrix);

	private:
		GLint _Texlocation;	// Texture location
		GLint _PMlocation;	// Projection Matrix location
		GLint _WMlocation;	// World Matrix location
		GLint _NMlocation;	// Normal Matrix location
		GLint _diffuseLocation;
		GLint _specularLocation;
		GLint _shininessLocation;
		GLint _lampON;

		glimac::Program _Program;
	};
}
