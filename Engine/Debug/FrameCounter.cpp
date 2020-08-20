#include <Debug/FrameCounter.h>

#include <GLFW/glfw3.h>

#include <iostream>

void FrameCounter::Sample() {
	double new_time = glfwGetTime();
	static double last_time = new_time;

	m_sample_count++;
	m_total_frametime += new_time - last_time;
	
	if (m_total_frametime > m_interval) {
		std::cout << "Performance information:" << std::endl
			<< "\tFPS: " << GetFPS() << std::endl
			<< "\tFrametime: " << GetFrametime() << std::endl;

		m_sample_count = 0;
		m_total_frametime = 0.0;
	}
	
	last_time = new_time;
}
