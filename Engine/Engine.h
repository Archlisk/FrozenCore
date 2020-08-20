#pragma once

#include <Core/Module.h>

#include <FC/Singleton.h>
#include <FC/String.h>

#include <vector>
#include <map>

class RenderEngine;
class Config;
class RenderWindow;
class InputHandler;
class GameObject;
class FrameCounter;
class ResourceManager;

class Engine 
{
	Singleton(Engine);
	
	public:
		~Engine();
		
		static void Run() { Engine::Get().Inter_Run(); }
		static void Exit() { Engine::Get().Inter_Exit(); }
		
		template<typename T>
		static T&	CreateObject(const String& name, T* ptr)	{ return Engine::Get().Inter_CreateObject(name, ptr); }
		static void DestroyObject(const String& name)			{ Engine::Get().Inter_DestroyObject(name); }
		
		static RenderEngine&	Render()	{ return Engine::Get().Inter_Render(); }
		static ResourceManager& Resource()	{ return Engine::Get().Inter_Resource(); }
		static InputHandler&	Input()		{ return Engine::Get().Inter_Input(); }
		static RenderWindow&	Window()	{ return Engine::Get().Inter_Window(); }
		
	private:
		void Init();
		
		void Inter_Run();
		void Inter_Exit() { m_exit = true; }
		
		template<typename T>
		T&		Inter_CreateObject(const String& name, T* ptr)	{ return *(T*)(m_game_objects[name] = ptr); }
		void	Inter_DestroyObject(const String& name)			{ m_game_objects.erase(name);  }
	
		RenderEngine&		Inter_Render()		{ return *m_render_engine.get(); }
		ResourceManager&	Inter_Resource()	{ return *m_resource_manager.get(); }
		InputHandler&		Inter_Input()		{ return *m_input_handler.get(); }
		RenderWindow&		Inter_Window()		{ return *m_window.get(); }
		
		
		Ref<Config>					m_config;
		Ref<RenderEngine>			m_render_engine;
		Ref<RenderWindow>			m_window;
		Ref<InputHandler>			m_input_handler;
		Ref<ResourceManager>		m_resource_manager;
		Ref<FrameCounter>		m_performance_tracker;
		
		std::vector<Module> m_modules;
		
		bool m_track_performance = false;
		
		std::map<String, GameObject*> m_game_objects;
		
		bool m_exit = false;
};
