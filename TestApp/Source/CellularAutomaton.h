#pragma once

#include <Core/GameObject.h>
#include <Core/Rect.h>
#include <Core/Window.h>
#include <Core/InputHandler.h>

#include <Render/RenderEngine.h>
#include <Resource/Texture.h>

#include <chrono>
#include <thread>
#include <cstring>

#define COLOR_ALIVE Color(255, 255, 255, 255)
#define COLOR_DEAD Color(0, 0, 0, 0)

#define DELAY_STEP 5

struct __attribute__((packed)) Color {
	Color() {}
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: b(b), g(g), r(r), a(a) {}

	bool operator==(const Color& other) {
		return *(uint32_t*)this == *(uint32_t*)&other;
	}

	uint8_t b;
	uint8_t g;
	uint8_t r;
	uint8_t a;
};

class CellularAutomaton : public GameObject {
public:
	CellularAutomaton() {
		Init();
	}
	
	void Init(float pixel_scale = 1.0f) {
		texture_res = (Vec2i)((Vec2)Engine::Get().GetWindow().GetResolution() * pixel_scale);
		draw_res = Engine::Get().GetWindow().GetResolution();
		texture_pixels = texture_res.x * texture_res.y;
	
		data[0] = new Color[texture_pixels];
		data[1] = new Color[texture_pixels];
		
		texture[0] = Texture(data[0], texture_res);
		texture[1] = Texture(data[1], texture_res);
		
		memset(data[0], 0, texture_pixels * sizeof(Color));
		
		for (int x = 1; x < texture_res.x - 1; x++) {
			for (int y = 1; y < texture_res.y - 1; y++) {
				if (rand() % 3)
					data[0][y * texture_res.x + x] = COLOR_DEAD;
				else
					data[0][y * texture_res.x + x] = COLOR_ALIVE;
			}
		}
		
		memcpy(data[1], data[0], texture_pixels * sizeof(Color));
	}
	
	void Update(double delta) override {
		InputHandler& input = Engine::Get().GetInputHandler();
	
		static float pixel_scale = 1.0f;
	
		if (input.GetKeyDown(GLFW_KEY_R))
			Init(pixel_scale);
			
		if (input.GetKeyDown(GLFW_KEY_UP))
			Init(pixel_scale /= 2);
			
		if (input.GetKeyDown(GLFW_KEY_DOWN))
			Init(pixel_scale *= 2);
			
		if (input.GetKeyDown(GLFW_KEY_SPACE))
			pause = !pause;
			
		if (input.GetKeyDown(GLFW_KEY_LEFT))
			if (delay < 15)
				delay *= delay;
			
		if (input.GetKeyDown(GLFW_KEY_RIGHT))
			if (delay > 3)
				delay = sqrt(delay);
		
		if (input.GetButton(GLFW_MOUSE_BUTTON_1))
			SetData(input.GetMousePosition() * pixel_scale, COLOR_ALIVE);
		
		if (input.GetButton(GLFW_MOUSE_BUTTON_2))
			SetData(input.GetMousePosition() * pixel_scale, COLOR_DEAD);
			
		if (input.GetKeyDown(GLFW_KEY_C)) {
			for (int x = 1; x < texture_res.x - 1; x++)
				for (int y = 1; y < texture_res.y - 1; y++)
					SetData(x, y, COLOR_DEAD);
		}
	}

	void DrawGUI() override {
		RenderEngine& render = Engine::Get().GetRenderEngine();
		Texture& tex = texture[current_texture];
		
		if (!pause) {
			render.SetUniform("draw_color", Vec3(1.0f));
			
			for (int x = 1; x < texture_res.x - 1; x++) {
				for (int y = 1; y < texture_res.y - 1; y++) {
					
					int close_alive = 0;
					
					if (GetData(x + 1, y) == COLOR_ALIVE)
						close_alive++;
					if (GetData(x - 1, y) == COLOR_ALIVE)
						close_alive++;
					if (GetData(x, y + 1) == COLOR_ALIVE)
						close_alive++;
					if (GetData(x, y - 1) == COLOR_ALIVE)
						close_alive++;
					if (GetData(x + 1, y + 1) == COLOR_ALIVE)
						close_alive++;
					if (GetData(x + 1, y - 1) == COLOR_ALIVE)
						close_alive++;
					if (GetData(x - 1, y + 1) == COLOR_ALIVE)
						close_alive++;
					if (GetData(x - 1, y - 1) == COLOR_ALIVE)
						close_alive++;
					
					if (GetData(x, y) == COLOR_ALIVE) {
						if (close_alive != 2 && close_alive != 3)
							SetData(x, y, COLOR_DEAD);
					}
					else {
						if (close_alive == 3)
							SetData(x, y, COLOR_ALIVE);
					}
				}
			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			
		}
		
		tex.Free();
		tex.Upload();
		current_texture = !current_texture;
		render.DrawGUIRect(tex, Rect(0, 0, draw_res));
		
		memcpy(data[!current_texture], data[current_texture], texture_pixels * sizeof(Color));
	}
	
	inline Color& GetData(int x, int y) {
		return data[current_texture][y * texture_res.x + x];
	}
	
	inline Color& GetData(const Vec2i& vec) {
		return data[current_texture][vec.y * texture_res.x + vec.x];
	}
	
	inline void SetData(int x, int y, const Color& color) {
		data[!current_texture][y * texture_res.x + x] = color;
	}
	
	inline void SetData(const Vec2i& vec, const Color& color) {
		data[!current_texture][vec.y * texture_res.x + vec.x] = color;
	}
	
private:
	Vec2i draw_res;
	Vec2i texture_res;
	
	volatile bool pause;
	
	int delay = 3;
	
	bool current_texture = 0;
	
	int texture_pixels;
	
	Color* data[2] = { nullptr, nullptr };
	Texture texture[2];
};
