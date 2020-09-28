#include "gepch.h"
#include "GameEngine/Application.h"

#include "GameEngine/Core.h"

#include "GameEngine/Log.h"


namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(GE_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(Application::OnWindowClose);
		dispatcher.Dispatch<WindowResizeEvent>(Application::OnWindowResize);

		// let each layer process the event until the event gets marked as handled
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		// send off to renderer

		return false;
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}

