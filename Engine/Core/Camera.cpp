#include <Engine.h>

#include <Core/Camera.h>
#include <Core/RenderWindow.h>

#include <Render/RenderEngine.h>

Camera::~Camera() {
	if (Engine::Render().GetCamera() == this)
		Engine::Render().SetCamera(nullptr);
}

const Mat4& Camera::GetProjectionMat() {
	if (m_projection_updated || aspect_ratio != Engine::Window().GetAspectRatio()) {
		m_projection_updated = false;
		return m_projection_mat = glm::perspective(glm::radians(m_fov), aspect_ratio = Engine::Window().GetAspectRatio(), m_near_clip, m_far_clip);
	}
	else 
		return m_projection_mat;
}
