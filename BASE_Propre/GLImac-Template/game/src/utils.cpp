#include "game/utils.hpp"

namespace game
{
	#define RELATIVE_ASSETS_PATH "/../assets/"
	#define RELATIVE_CONTENT_PATH "content/"
	#define RELATIVE_SHADERS_PATH "/shaders/"

	glimac::FilePath* gApplicationPath;

	void initApplicationPath(const char* argv)
	{
		gApplicationPath = new glimac::FilePath(argv);
	}

	std::string getScenesFilePath(const char* filename)
	{
		std::string s;
		s += gApplicationPath->dirPath().c_str() ;
		s += RELATIVE_ASSETS_PATH;
		s += filename;
		return s;
	}

	std::string getModelFilePath(const char* filename)
	{
		std::string s;
		s += gApplicationPath->dirPath().c_str() ;
		s += RELATIVE_ASSETS_PATH;
		s += RELATIVE_CONTENT_PATH;
		s += filename;
		return s;
	}

	void getShaderFilePath(glimac::FilePath* filePath, const char* filename)
	{
		*filePath = gApplicationPath->dirPath() + RELATIVE_SHADERS_PATH + filename;
	}

	void getTextureFilePath(glimac::FilePath* filePath, const char* filename)
	{
		*filePath = gApplicationPath->dirPath() + RELATIVE_ASSETS_PATH + RELATIVE_CONTENT_PATH + filename;
	}
}