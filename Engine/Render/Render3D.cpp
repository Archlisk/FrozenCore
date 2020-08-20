#include <Core/Camera.h>

#include <Render/RenderEngine.h>

#include <Resource/Material.h>

#include <GL/glew.h>

void RenderEngine::Render3DBegin() {
	glDepthFunc(GL_LESS);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void RenderEngine::Render3DEnd() {
	
}

void RenderEngine::DrawMesh(Mesh& model, Material& material, const Mat4& model_mat) {
	if (!m_active_camera)
		return;

	SetActiveTexture(material.diffuse);
	UseShaders(material.shader);
	
	glUniformMatrix4fv(m_shader->uniforms["projection_mat"], 1, GL_FALSE, &m_active_camera->GetProjectionMat()[0][0]);
	glUniformMatrix4fv(m_shader->uniforms["view_mat"], 1, GL_FALSE, &m_active_camera->GetViewMat()[0][0]);
	glUniformMatrix4fv(m_shader->uniforms["model_mat"], 1, GL_FALSE, &model_mat[0][0]);
	
	glUniform1i(m_shader->uniforms["diffuse_texture"], 0);
	
	BIND_COORD_BUFFER(model.gl_buffer_ids[0]);
	BIND_UV_BUFFER(model.gl_buffer_ids[1]);
	BIND_NORMAL_BUFFER(model.gl_buffer_ids[2]);
	
	BIND_ELEMENT_BUFFER(model.gl_element_buffer_id);
	
	switch (model.draw_mode) {
		case DrawMode::TRIANGLES:
			glDrawElements(GL_TRIANGLES, model.elements.size(), GL_UNSIGNED_INT, nullptr);
			break;
			
		case DrawMode::LINES:
			glDrawElements(GL_LINES, model.elements.size(), GL_UNSIGNED_INT, nullptr);
			break;
			
		case DrawMode::LINE_STRIP:
			glDrawElements(GL_LINE_STRIP, model.elements.size(), GL_UNSIGNED_INT, nullptr);
			break;
			
		case DrawMode::POINTS:
			glDrawElements(GL_POINTS, model.elements.size(), GL_UNSIGNED_INT, nullptr);
			break;
	}
}
