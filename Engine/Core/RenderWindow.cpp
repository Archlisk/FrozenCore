#include <Core/RenderWindow.h>

#include <GLFW/glfw3.h>

#include <Debug/Profiler.h>

RenderWindow::RenderWindow(Vec2i resolution, const String& title, bool resizable, bool fullscreen) 
	: m_resolution(resolution)
{
	glfwWindowHint(GLFW_RESIZABLE, resizable);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	if (fullscreen)
		m_glfw_window = glfwCreateWindow(resolution.x, resolution.y, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
		m_glfw_window = glfwCreateWindow(resolution.x, resolution.y, title.c_str(), nullptr, nullptr);
	
	glfwMakeContextCurrent(m_glfw_window);
}

RenderWindow::~RenderWindow() {
	glfwDestroyWindow(m_glfw_window);
}

void RenderWindow::SetResolution(const Vec2i& resolution) {
	if (resolution == m_resolution)
		return;

	glfwSetWindowSize(m_glfw_window, resolution.x, resolution.y);
	glfwGetWindowSize(m_glfw_window, &m_resolution.x, &m_resolution.y);
}

bool RenderWindow::ShouldClose() {
	return glfwWindowShouldClose(m_glfw_window);
}

void RenderWindow::SwapBuffers() {
	glfwSwapBuffers(m_glfw_window);
}

void RenderWindow::SetVSync(bool enabled) {
	glfwSwapInterval(enabled);
}
