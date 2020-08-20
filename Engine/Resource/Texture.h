#pragma once

#include <Core/GLM.h>

#include <FC/String.h>

class Texture {
public:	
	enum class Format {
		RGBA8,
		R8
	};

	Texture() {}

	Texture(Vec2i resolution, Format format = Format::RGBA8) 
		: resolution(resolution), format(format) {}

	~Texture() {
		if (gl_id)
			Free();
	}

	static Texture& Load(const String& path);
	
	void Upload(void* data);
	void Free();

	Vec2i resolution;
	Format format = Format::RGBA8;
	
	u32 gl_id = 0;
	
};
