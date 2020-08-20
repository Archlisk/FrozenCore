#pragma once

#include <Resource/Mesh.h>

#include <FC/String.h>
#include <FC/Map.h>

class RenderEngine;

class Texture;
class Shader;
class Font;

class ResourceManager {
public:
	~ResourceManager();

	Texture& GetTexture(const String& path);
	Mesh& GetMesh(const String& path, DrawMode draw_mode = DrawMode::TRIANGLES);
	Material& GetMaterial(const String& path);
	Shader& GetShader(const String& vert_path, const String frag_path);
	Font& GetFont(const String& path, int size);

private:
	Map<String, Texture*> m_textures;
	Map<String, Mesh*> m_meshes;
	Map<String, Material*> m_materials;
	Map<std::pair<String, String>, Shader*> m_shaders;
	Map<String, Font*> m_fonts;
};
