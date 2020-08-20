#pragma once

#include <Core/GLM.h>
#include <Core/GameObject.h>

class Camera : public GameObject {
public:
	Camera() {}
	Camera(const Vec3& position, Vec3 rotation, float fov = 75.0f, float near_clip = 0.01f, float far_clip = 100.0f) 
		: GameObject(position, rotation), m_fov(fov), m_near_clip(near_clip), m_far_clip(far_clip) {}
	
	~Camera();
	
	void SetPosition(const Vec3& position) { transform.position = position; m_view_updated = true; }
	void SetRotation(const Vec3& rotation) { transform.rotation = rotation; m_view_updated = true; }
	
	void SetFOV(float fov) { m_fov = fov; m_projection_updated = true; }
	void SetNearClip(float near_clip) { m_near_clip = near_clip; m_projection_updated = true; }
	void SetFarClip(float far_clip) { m_far_clip = far_clip; m_projection_updated = true; }
	
	float GetFOV() const { return m_fov; }
	float GetNearClip() const { return m_near_clip; }
	float GetFarClip() const { return m_far_clip; }
	
	const Mat4& GetProjectionMat();
	
	constexpr const Mat4& GetViewMat() {
		if (m_view_updated) {
			m_view_updated = false;
			return m_view_mat = glm::lookAt(transform.position, transform.position + transform.rotation, m_up);
		}
		else
			return m_view_mat;
	}

private:
	float m_fov = 75.0f;
	float m_near_clip = 0.01f;
	float m_far_clip = 100.0f;
	
	Vec3 m_up = Vec3(0, 1, 0);
	
	bool m_view_updated = true;
	bool m_projection_updated = true;
	
	float aspect_ratio = 0;
	
	Mat4 m_projection_mat;
	Mat4 m_view_mat;
};
