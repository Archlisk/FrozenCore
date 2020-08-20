#pragma once

#include <Core/GLM.h>

#include <Resource/Shader.h>
#include <Resource/Mesh.h>


#define GUI_DEPTH -0.01

#define BIND_COORD_BUFFER(buffer) \
	if (m_active_buffers[0] != buffer) { \
		glBindBuffer(GL_ARRAY_BUFFER, buffer); \
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); \
		m_active_buffers[0] = buffer; \
	}

#define BIND_UV_BUFFER(buffer) \
	if (m_active_buffers[1] != buffer) { \
		glBindBuffer(GL_ARRAY_BUFFER, buffer); \
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr); \
		m_active_buffers[1] = buffer; \
	}

#define BIND_NORMAL_BUFFER(buffer) \
	if (m_active_buffers[2] != buffer) { \
		glBindBuffer(GL_ARRAY_BUFFER, buffer); \
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr); \
		m_active_buffers[2] = buffer; \
	}
	
#define BIND_ELEMENT_BUFFER(buffer) \
	if (m_active_element_buffer != buffer) { \
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer); \
		m_active_element_buffer = buffer; \
	}



class Window;
class Camera;
class Shader;
class Texture;
class Font;

struct Rect;

class RenderEngine {
public:
	RenderEngine(const Vec2i& viewport_resolution);
	~RenderEngine();
	
	void SetCamera(Camera* camera) { m_active_camera = camera; }
	Camera* GetCamera() { return m_active_camera; }

	void Set2DShader(Shader& shader) { m_gui_shader = &shader; }
	void SetTextShader(Shader& shader) { m_text_shader = &shader; }
	
	void OnViewportResize(const Vec2i& viewport_resolution);

	void SetClearColor(const Vec3& color);
	void Clear();
	
	// 2D
	void Render2DEnd();
	void Render2DBegin();
	void DrawRect(Texture& texture, const Rect& rect);
	void DrawRectSliced(Texture& texture, const Rect& rect, int border_size);
	void DrawFont(Font& font, const String& text, const Vec2& position);
	
private: // Shaders
	void UseShaders(Shader* program);
	void WriteProgramUniforms(Shader& program);
	u32 CompileShader(const String& code, Shader::Type type);
	u32 LinkShaders(u32 vertex_id, u32 fragment_id);
public:
	Shader* CompileShaders(const String& vertex_path, const String& fragment_path);
	void SetUniform(const String& uniform_name, const Vec3& value);
	
	// Textures
	void InitTexture(Texture& texture, void* data);
	void SetTextureParams(Texture& texture, bool repeating = false, bool filtered = false);
	void DestroyTexture(Texture& texture);
	
	// Meshes
	void InitMesh(Mesh& mesh);
	void DestroyMesh(Mesh& mesh);
	
	// Fonts
	Font* GenerateFont(const String& path, int size);
	void DestroyFont(Font* font);
	
	// 3D
	void Render3DBegin();
	void Render3DEnd();
	void DrawMesh(Mesh& model, Material& texture, const Mat4& model_mat);

private:
	
	void SetActiveTexture(Texture* texture);

	Shader* m_shader;
	Shader* m_gui_shader;
	Shader* m_text_shader;
	
	Mesh m_sprite_mesh = Mesh (
		{ Vec3(0, 0, 0),	Vec3(1, 0, 0),	Vec3(0, 1, 0),	Vec3(1, 1, 0)	},
		{ Vec2(0, 0),		Vec2(1, 0),		Vec2(0, 1),		Vec2(1, 1)		},
		{},
		{ 0, 1, 2, 3, 2, 1 },
		DrawMode::TRIANGLES
	);
	
	u32 m_active_diffuse_texture_id = 0;
	
	u32 m_active_buffers[3] = { 0, 0, 0 };
	u32 m_active_element_buffer = 0;
	
	Camera* m_active_camera = nullptr;
	
	Mat4 m_gui_projection_mat = Mat4(1);
	Mat4 m_gui_view_mat = Mat4(1);
	
	Vec2i m_viewport_resolution;
};
