#include <Engine.h>

#include <Core/Config.h>
#include <Core/RenderWindow.h>
#include <Core/InputHandler.h>
#include <Core/ResourceManager.h>
#include <Core/Module.h>
#include <Core/GameObject.h>
#include <Core/GLM.h>

#include <Render/RenderEngine.h>

#include <Debug/FrameCounter.h>
#include <Debug/Profiler.h>

#include <GLFW/glfw3.h>


#define CONFIG(str) \
	(*m_config.get())[str]

#define ENGINE_CONFIG_PATH "Data/Engine.conf"

#undef Engine

void Engine::Init() {
	Profiler::Create();

    m_config = NewRef<Config>(ENGINE_CONFIG_PATH);
    
    if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW");
    
    Vec2i window_resolution = Vec2i(
		CONFIG("Window")["Resolution"]["Width"].IntValue(),
		CONFIG("Window")["Resolution"]["Height"].IntValue()
    );
    
    m_window = NewRef<RenderWindow>(
		window_resolution, 
		CONFIG("Window")["Title"].StringValue(),
		CONFIG("Window")["Resizable"].IntValue(),
		CONFIG("Window")["Fullscreen"].IntValue()
	);
	
	m_window->SetVSync(CONFIG("Window")["VSync"].IntValue());
	
	m_resource_manager = NewRef<ResourceManager>();
	
	m_render_engine = NewRef<RenderEngine>(m_window->GetResolution());
	m_render_engine->Set2DShader(Shader::Load(
		CONFIG("Graphics")["GUIShader"]["Vertex"].StringValue(),
		CONFIG("Graphics")["GUIShader"]["Fragment"].StringValue()
	));
	m_render_engine->SetTextShader(Shader::Load(
		CONFIG("Graphics")["TextShader"]["Vertex"].StringValue(),
		CONFIG("Graphics")["TextShader"]["Fragment"].StringValue()
	));
	
	m_render_engine->SetClearColor(Vec3(
		CONFIG("Graphics")["ClearColor"]["r"].FloatValue(),
		CONFIG("Graphics")["ClearColor"]["g"].FloatValue(),
		CONFIG("Graphics")["ClearColor"]["b"].FloatValue()
	));
	
	m_input_handler = NewRef<InputHandler>(*m_window.get());
	
	m_track_performance = CONFIG("Debug")["Performance"]["Enabled"].IntValue();
	if (m_track_performance) {
		m_performance_tracker = NewRef<FrameCounter>();
		m_performance_tracker->SetInterval(CONFIG("Debug")["Performance"]["PrintInterval"].FloatValue());
	}
	
	for (const Config::Value& val : CONFIG("Modules").Array())
		m_modules.emplace_back(val.StringValue());
}

Engine::~Engine() {
	for (auto& it : m_game_objects)
		delete it.second;
		
	Profiler::PrintSamples();
	Profiler::Destroy();
	
	glfwTerminate();
}

void Engine::Inter_Run() {
	float last_time = glfwGetTime();
	float current_time = glfwGetTime();

    while (!m_exit) {
		last_time = current_time;
		current_time = glfwGetTime();
    
		m_input_handler->Update();
		glfwPollEvents();
		
		if (m_window->ShouldClose())
			Exit();
    
		if (m_track_performance)
			m_performance_tracker->Sample();
		
		// Update
		double delta = current_time - last_time;
		for (Module& mod : m_modules)
			mod.Update(delta);
		for (auto& it : m_game_objects)
			it.second->Update(delta);
		
		// Render 3D
		m_render_engine->Render3DBegin();
		for (auto& it : m_game_objects)
			it.second->Render3D();
		m_render_engine->Render3DEnd();
		
		// Render 2D
		m_render_engine->Render2DBegin();
		for (auto& it : m_game_objects)
			it.second->Render2D();
		m_render_engine->Render2DEnd();
		
		// Done
		m_window->SwapBuffers();
		m_render_engine->Clear();
    }
}
