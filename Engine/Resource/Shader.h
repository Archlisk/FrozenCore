#pragma once

#include <Engine.h>

#include <Core/ResourceManager.h>

#include <FC/Map.h>

class Shader {
public:
	enum class Type {
		VertexShader,
		FragmentShader
	};

	Shader(u32 id) : gl_id(id) {}
	
	static Shader& Load(const String& vert_path, const String& frag_path) { 
		return Engine::Resource().GetShader(vert_path, frag_path);
	}
	
	u32 gl_id;
	Map<String, u32> uniforms;
};
