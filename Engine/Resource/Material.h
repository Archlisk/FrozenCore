#pragma once

class Texture;
class Shader;

struct Material {

	Material() {}
	
	static Material& Load(const std::string& path);
	
	Texture* diffuse;
	Texture* normal;
	Texture* specular;
	
	Shader* shader;
};
