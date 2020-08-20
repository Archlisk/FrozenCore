#pragma once

#include <Core/GLM.h>

#include <vector>

struct Material;

enum class DrawMode {
	TRIANGLES,
	LINES,
	LINE_STRIP,
	POINTS
};

class Mesh {
public:
	Mesh() {}
	
	Mesh(
		const std::vector<Vec3>& vertices, 
		const std::vector<Vec2>& uvs, 
		const std::vector<Vec3>& normals, 
		const std::vector<u32>& elements,
		DrawMode draw_mode
	) :	vertices(vertices), uvs(uvs), normals(normals), elements(elements), draw_mode(draw_mode) {}
	
	static Mesh& Load(const std::string& path);
	
	std::vector<Vec3> vertices;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	
	u32 gl_buffer_ids[3] = { 0, 0, 0 };

	std::vector<u32> elements;
	
	u32 gl_element_buffer_id = 0;
	
	DrawMode draw_mode;
};
