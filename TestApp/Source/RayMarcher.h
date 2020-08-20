#pragma once

#include <GameObject.h>
#include <Rect.h>
#include <Texture.h>
#include <RenderEngine.h>
#include <Window.h>
#include <vector>

#include <thread>

struct Sphere {
	Vec3 position;
	float radius;
	
	float movement_mult;
	
	bool reflective;
	
	float orig_x = position.x;
	
	void Update(double delta) {
		static double time = 0.0f;
		time += delta;
		position.x = orig_x + sin(time) * movement_mult;
	}
};

class RayMarcher : public GameObject {
public:
	RayMarcher() {}

	void Update(double delta) override {
		for (Sphere& sphere : spheres)
			sphere.Update(delta);
	}

	inline void RenderArea(const Rect& rect) {
		int x2 = rect.x + rect.w;
		int y2 = rect.y + rect.h;
		
		for (int y = rect.y; y < y2; y++) {
			int offs = (rect.x + y * res.x) * 4;
			
			for (int x = rect.x; x < x2; x++) {
				Vec3 ray_pos(x - res_half.x, y - res_half.y, 0);
				
				const Sphere* hit = Raycast(ray_pos, ray_dir);
				
				if (hit)
					(*(uint32_t*)&tex_data[offs + 0]) = 0xFFFFFFFF;	// Blue
				else
					(*(uint32_t*)&tex_data[offs + 0]) = 0xFF000000;	// Blue
				
				offs += 4;
			}
		}
	}

	void DrawGUI() override {
		RenderEngine& render = Engine::Get().GetRenderEngine();
		
		tex_data = new unsigned char[tex_bytes];
		
		std::array<std::thread, 16> arr = {
//			std::thread(&RayMarcher::RenderArea, this, Rect(0, 0, res_half.x, res_half.y)),
//			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x, 0, res_half.x, res_half.y)),
//			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x, res_half.y, res_half.x, res_half.y)),
//			std::thread(&RayMarcher::RenderArea, this, Rect(0, res_half.y, res_half.x, res_half.y)),

			std::thread(&RayMarcher::RenderArea, this, Rect(0, 0, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_quat.x, 0, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_quat.x, res_quat.y, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(0, res_quat.y, res_quat.x, res_quat.y)),
			
			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x, 0, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x + res_quat.x, 0, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x + res_quat.x, res_quat.y, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x, res_quat.y, res_quat.x, res_quat.y)),
			
			std::thread(&RayMarcher::RenderArea, this, Rect(0, res_half.y, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_quat.x, res_half.y, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_quat.x, res_half.y + res_quat.y, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(0, res_half.y + res_quat.y, res_quat.x, res_quat.y)),
			
			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x, res_half.y, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x + res_quat.x, res_half.y, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x + res_quat.x, res_half.y + res_quat.y, res_quat.x, res_quat.y)),
			std::thread(&RayMarcher::RenderArea, this, Rect(res_half.x, res_half.y + res_quat.y, res_quat.x, res_quat.y)),
		};
		
		for (std::thread& trd : arr)
			trd.join();
		
		Texture ray_tex(tex_data, 0, res);
		
		render.InitTexture(ray_tex);
		render.DrawGUIRect(ray_tex, Rect(0, 0, res));
		render.DestroyTexture(ray_tex);
	}
	
	inline const Sphere* Raycast(const Vec3& pos_a, const Vec3& dir, const Sphere* src = nullptr) const {
		Vec3 pos = pos_a;
	
		while (fabs(pos.x) < max_dist && fabs(pos.y) < max_dist && fabs(pos.z) < max_dist) {
			const Sphere* hit = nullptr;
			float min_dist = max_dist;
			
			for (const Sphere& sphere : spheres) {
				if (&sphere == src)
					continue;
			
				float dist = glm::distance(sphere.position, pos) - sphere.radius;
				
				if (dist < min_dist) {
					hit = &sphere;
					min_dist = dist;
				
					if (dist < 1.0f) {
						if (hit->reflective && !src)
							return Raycast(pos, glm::reflect(dir, glm::normalize(pos - hit->position)), hit);
						return hit;
					}
				}
			}
			
			pos += dir * min_dist;
		}
		
		return nullptr;
	}
	
private:
	Vec2i res = Engine::Get().GetWindow().GetResolution();
	Vec2 res_half = res / 2;
	Vec2 res_quat = res / 4;
	float aspect = Engine::Get().GetWindow().GetAspectRatio();
	
	float max_dist = 2000.0f;
	
	int tex_bytes = res.x * res.y * 4;
	unsigned char* tex_data;
	
	Vec3 ray_dir = Vec3(0, 0, 1);
	
	std::vector<Sphere> spheres = {
		{{-450.0f, 0.0f, 750.0f}, 200.0f, 50.0f, false},
		{{0.0f, 0.0f, 800.0f}, 200.0f, 100.0f, true},
		{{450.0f, 0.0f, 1000.0f}, 200.0f, 200.0f, false}
	};
};
