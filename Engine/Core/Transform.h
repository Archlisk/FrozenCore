#pragma once

#include <Core/GLM.h>

struct Transform {
public:
	
	Transform() {}
	Transform(const Vec3 position, const Vec3 rotation, const Vec3 scale) 
		: position(position), rotation(rotation), scale(scale) {}
	
	Vec3 position = Vec3(0);
	Vec3 rotation = Vec3(0);
	Vec3 scale = Vec3(1);
	
	Mat4 GetMatrix() {
		return
			glm::rotate(
				glm::scale(
					glm::translate(
						Mat4(1), position
					),
					scale
				),
				rotation.x,
				Vec3(0, 1, 0)
			);
	}
};
