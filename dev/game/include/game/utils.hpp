#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

#include <glimac/FilePath.hpp>

namespace game
{
	extern glimac::FilePath* gApplicationPath;

	void initApplicationPath(const char* argv);									// Initialize the applicationPath
	std::string getScenesFilePath(const char* filename);						// Return correct path string to a scene file
	std::string getModelFilePath(const char* filename);							// Return correct path string to a 3D model file
	void getShaderFilePath(glimac::FilePath* filePath, const char* filename);	// Return correct glimac::FilePath to a shader file
	void getTextureFilePath(glimac::FilePath* filePath, const char* filename);	// Return correct glimac::FilePath to a texture
}