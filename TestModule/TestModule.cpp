#include <Engine.h>

#include <Core/Camera.h>
#include <Core/InputHandler.h>
#include <Core/RenderWindow.h>

#include <Render/RenderEngine.h>

#include <Resource/Mesh.h>
#include <Resource/Material.h>
#include <Resource/Font.h>

#include <Debug/Profiler.h>

#include <iostream>


class MeshRenderer : public GameObject 
{
	public:
		void Render3D() override 
		{
			Engine::Render().DrawMesh(m_mesh, m_material, transform.GetMatrix());
		}
		
		void Update(double) override 
		{
			static Vec3* edited = nullptr;
			
			InputHandler& input = Engine::Input();
			Vec2 mouse_pos = input.GetMousePosition();
			
			mouse_pos.x = -mouse_pos.x;
			
			if (input.GetKeyDown(GLFW_KEY_Q)) {
				if (edited != &transform.position)
					edited = &transform.position;
				else
					edited = nullptr;
			}
			
			if (input.GetKeyDown(GLFW_KEY_W)) {
				if (edited != &transform.rotation)
					edited = &transform.rotation;
				else
					edited = nullptr;
			}
			
			if (input.GetKeyDown(GLFW_KEY_E)) {
				if (edited != &transform.scale)
					edited = &transform.scale;
				else
					edited = nullptr;
			}
			
			if (edited) {
				static Vec3 offset;
				Vec2 res = (Vec2)Engine::Window().GetResolution();
				
				if (input.GetButtonDown(GLFW_MOUSE_BUTTON_LEFT))
					offset = *edited - Vec3(mouse_pos / res, 0) * 12.0f;
				
				else if (input.GetButton(GLFW_MOUSE_BUTTON_LEFT))
					*edited = Vec3(mouse_pos / res, 0) * 12.0f + offset;
			}
		}
		
	private:
		Mesh& m_mesh = Mesh::Load("Data/Models/Sphere.obj");
		Material& m_material = Material::Load("Data/Materials/Example.mat");
};



extern "C" 
void OnLoad(Engine&) 
{
	std::cout << "TestModule loaded successfully" << std::endl;
	
	GameObject::Create("Mesh", new MeshRenderer());
	
	Camera& cam = GameObject::Create("1", new Camera(Vec3(0, 0, -10), Vec3(0, 0, 1)));
	Engine::Render().SetCamera(&cam);
}

extern "C" 
void OnUnload() 
{
	
}

extern "C" 
void OnUpdate(double) 
{
	
}
