#include <Engine.h>

#include <Core/ResourceManager.h>

#include <Resource/Material.h>

Material& Material::Load(const String& path) {
	return Engine::Resource().GetMaterial(path);
}
