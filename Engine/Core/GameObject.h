#pragma once

#include <Engine.h>

#include <Core/Transform.h>

class GameObject {
public:
	GameObject(const Vec3 position = Vec3(0), const Vec3 rotation = Vec3(0), const Vec3 scale	= Vec3(1)) 
		: transform(position, rotation, scale){}
	
	virtual ~GameObject() {}
	
	virtual void Render3D() {}
	virtual void Render2D() {}
	virtual void Update(double) {}

	template<typename T>
	static inline T& Create(const String& name, T* ptr) {
		return Engine::Get().CreateObject(name, ptr);
	}

	Transform transform;
};
