#pragma once

#include <Core/GLM.h>

#include <FC/String.h>

class GLFWwindow;

class RenderWindow {
public:
	RenderWindow(Vec2i resolution, const String& title, bool resizable = false, bool fullscreen = false);
	~RenderWindow();
	
	bool ShouldClose();
	
	const Vec2i& GetResolution() const { return m_resolution; }
	void SetResolution(const Vec2i& resolution);
	
	float GetAspectRatio() const { return (float)m_resolution.x / (float)m_resolution.y; }
	
	void SetVSync(bool enabled);
	
	GLFWwindow* GetGLFWWindow() { return m_glfw_window; }
	
	void SwapBuffers();
	
private:
	GLFWwindow* m_glfw_window;
	Vec2i m_resolution;
};
