#pragma once

#include <Core/GLM.h>

#include <map>

class Texture;

class Font {
public:

	struct Character {
		Character() {}
		
		Character(Texture* texture, Vec2i bearing, int advance)
			: texture(texture), bearing(bearing), advance(advance) {}
	
		~Character() {
		};
		
		Texture* texture = nullptr;
		Vec2i bearing;
		int advance;
	};
	
	~Font();
	
	static Font& Load(const String& path, int size);
	
	std::map<char, Character> charset;
};
