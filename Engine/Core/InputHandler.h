#pragma once

#include <Core/GLM.h>

#include <GLFW/glfw3.h>

class RenderWindow;
class GLFWwindow;

enum class MouseMode {
	NORMAL,
	CAPTURED
};

class InputHandler {
public:
	InputHandler(RenderWindow& window);
	~InputHandler();
	
	inline void OnKeyboardEvent(int key, int action) { m_keymap[key] = action; }
	inline void OnMousePositionEvent(const Vec2& position);
	inline void OnMouseButtonEvent(int button, int action) { m_buttonmap[button] = action; }

	void Update();
	
	void SetMousePos(const Vec2& position);
	
	inline bool GetButton(int button) { return m_buttonmap[button]; }
	inline bool GetButtonDown(int button) { return (m_buttonmap[button] && !m_last_buttonmap[button]); }
	inline bool GetButtonUp(int button) { return (!m_buttonmap[button] && m_last_buttonmap[button]); }

	inline bool GetKey(int key) { return m_keymap[key]; }
	inline bool GetKeyDown(int key) { return (m_keymap[key] && !m_last_keymap[key]); }
	inline bool GetKeyUp(int key) { return (!m_keymap[key] && m_last_keymap[key]); }
	
	inline Vec2 GetMousePosition() { return m_mouse_pos; }

private:
	static void KeyboardCallback(GLFWwindow*, int key, int, int action, int);
	static void MouseButtonCallback(GLFWwindow*, int button, int action, int);
	static void MousePositionCallback(GLFWwindow*, double x, double y);

	bool m_keymap[GLFW_KEY_LAST];
	bool m_last_keymap[GLFW_KEY_LAST];
	
	bool m_buttonmap[GLFW_MOUSE_BUTTON_LAST];
	bool m_last_buttonmap[GLFW_MOUSE_BUTTON_LAST];

	Vec2 m_mouse_pos;
	MouseMode m_mouse_mode = MouseMode::NORMAL;
	
	RenderWindow* m_window;
};
