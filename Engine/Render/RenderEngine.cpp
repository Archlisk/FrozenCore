#include <Render/RenderEngine.h>

#include <FC/String.h>

#include <GL/glew.h>

RenderEngine::RenderEngine(const Vec2i& viewport_resolution) 
	: m_shader(0), m_gui_shader(0), m_viewport_resolution(viewport_resolution)
{
	glewExperimental = true;
	int error = glewInit();
	if (error != 0)
		throw RuntimeException(String("Failed to initialize GLEW: ") + (const char*)glewGetErrorString(error));
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	u32 vert_arr;
	glGenVertexArrays(1, &vert_arr);
	glBindVertexArray(vert_arr);
	
	InitMesh(m_sprite_mesh);
	
	m_gui_projection_mat = glm::ortho(0.0f, (float)viewport_resolution.x, 0.0f, (float)viewport_resolution.y, 0.01f, 100.0f);
}

RenderEngine::~RenderEngine() {
	
}

void RenderEngine::OnViewportResize(const Vec2i& viewport_resolution) {
	glViewport(0, 0, viewport_resolution.x, viewport_resolution.y);
	
	m_viewport_resolution = viewport_resolution;
}

void RenderEngine::SetClearColor(const Vec3& color) {
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void RenderEngine::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
