#include <Engine.h>

#include <Core/InputHandler.h>
#include <Core/RenderWindow.h>

#include <GLFW/glfw3.h>

#include <cstring>

void InputHandler::KeyboardCallback(GLFWwindow*, int key, int, int action, int) {
	Engine::Input().OnKeyboardEvent(key, action);
}

void InputHandler::MousePositionCallback(GLFWwindow*, double x, double y) {
	Engine::Input().OnMousePositionEvent(Vec2(x, y));
}

void InputHandler::MouseButtonCallback(GLFWwindow*, int button, int action, int) {
	Engine::Input().OnMouseButtonEvent(button, action);
}

void InputHandler::OnMousePositionEvent(const Vec2& position) {
	m_mouse_pos = Vec2(position.x, (float)m_window->GetResolution().y - position.y);
}

InputHandler::InputHandler(RenderWindow& window) 
		: m_window(&window) {
	
	memset(m_keymap, 0, GLFW_KEY_LAST);
	memset(m_last_keymap, 0, GLFW_KEY_LAST);
	
	memset(m_buttonmap, 0, GLFW_MOUSE_BUTTON_LAST);
	memset(m_last_buttonmap, 0, GLFW_MOUSE_BUTTON_LAST);
	
	glfwSetKeyCallback(m_window->GetGLFWWindow(), KeyboardCallback);
	glfwSetCursorPosCallback(m_window->GetGLFWWindow(), MousePositionCallback);
	glfwSetMouseButtonCallback(m_window->GetGLFWWindow(), MouseButtonCallback);
}

InputHandler::~InputHandler() {
	
}

void InputHandler::Update() {
	memcpy(m_last_keymap, m_keymap, GLFW_KEY_LAST);
	memcpy(m_last_buttonmap, m_buttonmap, GLFW_MOUSE_BUTTON_LAST);
}

void InputHandler::SetMousePos(const Vec2& position) {
	m_mouse_pos = position;
	glfwSetCursorPos(m_window->GetGLFWWindow(), position.x, position.y);
}
