#include <Core/Rect.h>

#include <Render/RenderEngine.h>

#include <Resource/Texture.h>
#include <Resource/Font.h>

#include <GL/glew.h>


void RenderEngine::Render2DBegin() {
	glDepthFunc(GL_ALWAYS);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void RenderEngine::Render2DEnd() {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void RenderEngine::DrawRect(Texture& texture, const Rect& rect) {
	SetActiveTexture(&texture);
	
	Mat4 model_matrix = 
		glm::scale(
			glm::translate(Mat4(1), Vec3(rect.x, rect.y, GUI_DEPTH)), 
			Vec3(rect.w, rect.h, 1)
		);
	
	glUniformMatrix4fv(m_shader->uniforms["projection_mat"], 1, GL_FALSE, &m_gui_projection_mat[0][0]);
	glUniformMatrix4fv(m_shader->uniforms["view_mat"], 1, GL_FALSE, &m_gui_view_mat[0][0]);
	glUniformMatrix4fv(m_shader->uniforms["model_mat"], 1, GL_FALSE, &model_matrix[0][0]);
	
	glUniform1i(m_shader->uniforms["diffuse_texture"], 0);
	
	BIND_COORD_BUFFER(m_sprite_mesh.gl_buffer_ids[0]);
	BIND_UV_BUFFER(m_sprite_mesh.gl_buffer_ids[1]);
	
	BIND_ELEMENT_BUFFER(m_sprite_mesh.gl_element_buffer_id);
	
	glDrawElements(GL_TRIANGLES, m_sprite_mesh.elements.size(), GL_UNSIGNED_INT, nullptr);
}

// TODO: Make 9 slice drawing run on the GPU instead of creating a ton of buffers

void RenderEngine::DrawRectSliced(Texture& texture, const Rect& rect, int border_size) {
	SetActiveTexture(&texture);
	
	Vec2 border_uv = Vec2((float)border_size / texture.resolution.x, (float)border_size / texture.resolution.y);
	
	Mesh model;
	model.vertices = {
		{ 0, 0, GUI_DEPTH }, { border_size,  0, GUI_DEPTH }, { rect.w - border_size, 0, GUI_DEPTH }, { rect.w, 0, GUI_DEPTH },
		{ 0, border_size, GUI_DEPTH }, { border_size,  border_size, GUI_DEPTH }, { rect.w - border_size, border_size, GUI_DEPTH }, { rect.w, border_size, GUI_DEPTH },
		{ 0, rect.h - border_size, GUI_DEPTH }, { border_size, rect.h - border_size, GUI_DEPTH }, { rect.w - border_size, rect.h - border_size, GUI_DEPTH }, { rect.w, rect.h - border_size, GUI_DEPTH },
		{ 0, rect.h, GUI_DEPTH }, { border_size, rect.h, GUI_DEPTH }, { rect.w - border_size, rect.h, GUI_DEPTH }, { rect.w, rect.h, GUI_DEPTH },
	};
	model.uvs = {
		{ 0.0f, 0.0f }, { border_uv.x, 0.0f }, { 1.0f - border_uv.x, 0.0f }, { 1.0f, 0.0f },
		{ 0.0f, border_uv.y }, { border_uv.x, border_uv.y }, { 1.0f - border_uv.x, border_uv.y }, { 1.0f, border_uv.y },
		{ 0.0f, 1.0f - border_uv.y }, { border_uv.x, 1.0f - border_uv.y }, { 1.0f - border_uv.x, 1.0f - border_uv.y }, { 1.0f, 1.0f - border_uv.y },
		{ 0.0f, 1.0f }, { border_uv.x, 1.0f }, { 1.0f - border_uv.x, 1.0f }, { 1.0f, 1.0f }
	};
	model.elements = {
		4, 0, 1,	4, 1, 5,	5, 1, 2,	5, 2, 6,	6, 2, 3,	6, 3, 7,	
		8, 4, 5,	8, 5, 9,	9, 5, 6,	9, 6, 10,	10, 6, 7,	10, 7, 11,	
		12, 8, 9,	12, 9, 13,	13, 9, 10,	13, 10, 14,	14, 10, 11,	14, 11, 15
	};
	
	InitMesh(model);
	
	Mat4 model_matrix = glm::translate(Mat4(1), Vec3(rect.x, rect.y, 0));
	
	glUniformMatrix4fv(m_shader->uniforms["projection_mat"], 1, GL_FALSE, &m_gui_projection_mat[0][0]);
	glUniformMatrix4fv(m_shader->uniforms["view_mat"], 1, GL_FALSE, &m_gui_view_mat[0][0]);
	glUniformMatrix4fv(m_shader->uniforms["model_mat"], 1, GL_FALSE, &model_matrix[0][0]);
	
	glUniform1i(m_shader->uniforms["diffuse_texture"], 0);
	
	BIND_COORD_BUFFER(model.gl_buffer_ids[0]);
	BIND_UV_BUFFER(model.gl_buffer_ids[1]);
	
	BIND_ELEMENT_BUFFER(model.gl_element_buffer_id);
	
	glDrawElements(GL_TRIANGLES, model.elements.size(), GL_UNSIGNED_INT, nullptr);
	
	DestroyMesh(model);
}

void RenderEngine::DrawFont(Font& font, const String& text, const Vec2& position) {
	UseShaders(m_text_shader); // TODO: Fix this garbage
	
	int offsetx = position.x;
	
	for (u32 i = 0; i < text.size(); i++) {
		Font::Character ch = font.charset[text[i]];
		
		DrawRect(*ch.texture, Rect(offsetx, position.y + ch.bearing.y - ch.texture->resolution.y, ch.texture->resolution));
		
		offsetx += (ch.advance >> 6);
	}
	
	UseShaders(m_gui_shader); // TODO: Fix this garbage
}
