#include <Render/RenderEngine.h>

#include <Resource/Font.h>
#include <Resource/Texture.h>

#include <freetype2/ft2build.h>

#include FT_FREETYPE_H

Font* RenderEngine::GenerateFont(const String& path, int size) {
	FT_Library ft;
	
	if (FT_Init_FreeType(&ft))
		throw RuntimeException("Failed to initialize FreeType2");
	
	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face))
		throw RuntimeException("Failed to create FreeType2 face");
	
	FT_Set_Pixel_Sizes(face, 0, size);
	
	Font* font = new Font();
	
	for (int i = 0; i < 256; i++) {
		
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
			throw RuntimeException(String("Failed to load FreeType2 glyph '") + (char)i + "'");
		
		Texture* texture = new Texture(Vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows), Texture::Format::R8);
		texture->Upload(face->glyph->bitmap.buffer);
		
		Font::Character character;
		character.texture = texture;
		character.bearing = Vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top);
		character.advance = face->glyph->advance.x;
		
		font->charset.insert(std::make_pair(i, character));
	}
	
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	
	return font;
}

void RenderEngine::DestroyFont(Font* font) {
	
}
