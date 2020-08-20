#include <Engine.h>

#include <Core/ResourceManager.h>
#include <Render/RenderEngine.h>

#include <Resource/Mesh.h>
#include <Resource/Material.h>


Mesh& Mesh::Load(const std::string& path) { 
	return Engine::Resource().GetMesh(path);
}
