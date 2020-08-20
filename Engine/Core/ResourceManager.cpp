#include <Core/ResourceManager.h>
#include <Core/Helpers.h>
#include <Core/Config.h>

#include <Render/RenderEngine.h>
#include <Resource/Material.h>
#include <Resource/Font.h>

#include <Resource/LoadTexture.h>
#include <Resource/LoadModel.h>

#include <iostream>

ResourceManager::~ResourceManager() {
	for (auto it : m_textures)
		delete it.second;
	for (auto it : m_meshes)
		delete it.second;
	for (auto it : m_materials)
		delete it.second;
	for (auto it : m_shaders)
		delete it.second;
	for (auto it : m_fonts)
		delete it.second;
}

Texture& ResourceManager::GetTexture(const String& path) {
	auto it = m_textures.find(path);
	if (it != m_textures.end())
		return *it->second;

	std::cout << "Loading texture '" << path << "'" << std::endl;

	std::pair<Texture*, u8*> tex_data;

	if (StrEndsWith(path, ".bmp")) {
		tex_data = LoadBMP(path);
		m_textures[path] = tex_data.first;
	}
	else 
		throw RuntimeException("Unsupported file type");
		
	Texture& texture = *m_textures[path];
	Engine::Render().InitTexture(texture, tex_data.second);
	delete[] tex_data.second;
	
	return texture;
}

Mesh& ResourceManager::GetMesh(const String& path, DrawMode draw_mode) {
	auto it = m_meshes.find(path);
	if (it != m_meshes.end())
		return *it->second;
	
	std::cout << "Loading mesh '" << path << "'" << std::endl;
	
	if (StrEndsWith(path, ".obj"))
		m_meshes[path] = LoadOBJ(path);
	else 
		throw RuntimeException("Unsupported file type");
		
	Mesh& model = *m_meshes[path];
	model.draw_mode = draw_mode;
	Engine::Render().InitMesh(model);
	return model;
}

Material& ResourceManager::GetMaterial(const String& path) {
	auto it = m_materials.find(path);
	if (it != m_materials.end())
		return *it->second;
		
	std::cout << "Loading material '" << path << "'" << std::endl;
	
	if (!StrEndsWith(path, ".mat"))
		throw RuntimeException("Unsupported file type");
	
	Material* material = new Material();
	m_materials[path] = material;
	
	Config conf(path);
	material->diffuse = &ResourceManager::GetTexture(conf["Diffuse"].StringValue());
	material->shader = &ResourceManager::GetShader(conf["Shader"]["Vertex"].StringValue(), conf["Shader"]["Fragment"].StringValue());
	
	return *material;
}

Shader& ResourceManager::GetShader(const String& vert_path, const String frag_path) {
	auto it = m_shaders.find(std::make_pair(vert_path, frag_path));
	if (it != m_shaders.end())
		return *it->second;
		
	Shader* shader = Engine::Render().CompileShaders(vert_path, frag_path);
	m_shaders[std::make_pair(vert_path, frag_path)] = shader;
	return *shader;
}

Font& ResourceManager::GetFont(const String& path, int size) {
	auto it = m_fonts.find(path);
	if (it != m_fonts.end())
		return *it->second;
	
	std::cout << "Loading font '" << path << "'" << std::endl;
	
	Font* font = Engine::Render().GenerateFont(path, size);
	m_fonts[path] = font;
	return *font;
}
