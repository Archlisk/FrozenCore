#include <Engine.h>

#include <Core/ResourceManager.h>

#include <Render/RenderEngine.h>
#include <Resource/Texture.h>


Texture& Texture::Load(const String& path) {
	return Engine::Resource().GetTexture(path);
}

void Texture::Upload(void* data) {
	Engine::Render().InitTexture(*this, data);
}

void Texture::Free() {
	Engine::Render().DestroyTexture(*this);
}
