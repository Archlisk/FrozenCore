#include <Engine.h>

#include <Core/ResourceManager.h>

#include <Resource/Font.h>
#include <Resource/Texture.h>

Font::~Font() {
	for (auto& it : charset)
		delete it.second.texture;
}

Font& Font::Load(const String& path, int size) {
	return Engine::Resource().GetFont(path, size);
}
