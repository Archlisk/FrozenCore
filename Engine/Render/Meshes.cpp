#include <Render/RenderEngine.h>

#include <GL/glew.h>


void RenderEngine::InitMesh(Mesh& model) {
    glGenBuffers(1, &model.gl_element_buffer_id);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.gl_element_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.elements.size() * sizeof(u32), model.elements.data(), GL_STATIC_DRAW);
    
    glGenBuffers(3, &model.gl_buffer_ids[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, model.gl_buffer_ids[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(Vec3), model.vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, model.gl_buffer_ids[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, model.uvs.size() * sizeof(Vec2), model.uvs.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, model.gl_buffer_ids[2]);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(Vec3), model.normals.data(), GL_STATIC_DRAW);
    
    m_active_buffers[0] = 0;
    m_active_buffers[1] = 0;
    m_active_buffers[2] = 0;
    m_active_element_buffer = 0;
}

void RenderEngine::DestroyMesh(Mesh& model) {
	glDeleteBuffers(3, model.gl_buffer_ids);
	glDeleteBuffers(1, &model.gl_element_buffer_id);
	
	m_active_buffers[0] = 0;
    m_active_buffers[1] = 0;
    m_active_buffers[2] = 0;
    m_active_element_buffer = 0;
}
