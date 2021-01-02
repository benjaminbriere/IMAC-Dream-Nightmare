#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <assimp/scene.h>
#include <json/json.h>

#include <glimac/FilePath.hpp>

#include "utils.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "FPSCamera.hpp"
#include "Light.hpp"
#include "Light_Ambient.hpp"
#include "Light_Directional.hpp"
#include "Light_Point.hpp"

namespace game
{
	class Scene
	{
		private:
			ShaderProgram* _Program;
			
			std::vector<Light*> _Lights;


		public:
			FPSCamera _Camera;
			std::vector<Mesh*> _Meshes;

			Scene(ShaderProgram* program);
			~Scene();

			bool init(const char* sceneFilePath);		
			void render(int lamp);
						
	};
}
