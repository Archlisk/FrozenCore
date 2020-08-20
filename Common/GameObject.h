#pragma once

#include <GLM.h>

class GameObject {
public:
	GameObject() {}
	
	GameObject(const Vec3& position, const Vec3& rotation, const Vec3& scale = Vec3(1)) 
		: m_position(position), m_rotation(rotation), m_scale(scale) {}
	
	virtual ~GameObject() {}
	
	virtual void Render3D() {}
	virtual void Render2D() {}
	virtual void Update(double) {}

	virtual void SetPosition(const Vec3& position) { m_position = position; }
	const Vec3& GetPosition() const { return m_position; }

	virtual void SetRotation(const Vec3& rotation) { m_rotation = rotation; }
	const Vec3& GetRotation() const { return m_rotation; }
	
	virtual void SetScale(const Vec3& scale) { m_scale = scale; }
	const Vec3& GetScale() const { return m_scale; }
	
//	template<typename T, typename... Targs>
//	inline static Handle<T> Create(Targs... args) {
//		return Engine::Get().CreateObject<T>(new T(args...));
//	}
	
protected:
	Vec3 m_position = Vec3(0);
	Vec3 m_rotation = Vec3(0);
	Vec3 m_scale = Vec3(1);
};
