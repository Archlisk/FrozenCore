#include <Render/RenderEngine.h>

#include <Resource/Texture.h>

#include <GL/glew.h>


void RenderEngine::SetActiveTexture(Texture* texture) {
	if (m_active_diffuse_texture_id != texture->gl_id) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->gl_id);
		m_active_diffuse_texture_id = texture->gl_id;
	}
}

void RenderEngine::InitTexture(Texture& texture, void* data) {
	glActiveTexture(GL_TEXTURE0);
	
	glGenTextures(1, &texture.gl_id);
	glBindTexture(GL_TEXTURE_2D, texture.gl_id);
	m_active_diffuse_texture_id = texture.gl_id;
	
	
	switch (texture.format) {
		case Texture::Format::RGBA8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.resolution.x, texture.resolution.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
			break;
		
		case Texture::Format::R8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, texture.resolution.x, texture.resolution.y, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			break;
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glGenerateMipmap(GL_TEXTURE_2D);
}

void RenderEngine::SetTextureParams(Texture& texture, bool repeating, bool filtered) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.gl_id);
	m_active_diffuse_texture_id = texture.gl_id;

	if (repeating) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	
	if (filtered) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
}

void RenderEngine::DestroyTexture(Texture& texture) {
	glDeleteTextures(1, &texture.gl_id);
}
