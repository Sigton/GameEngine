#pragma once

#include "GameEngine/Core.h"

#include "GameEngine/Window.h"

#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"

#include "GameEngine/LayerStack.h"

namespace GameEngine {

	class Application
	{
	public:
		Application(const std::string& name = "Game App");
		virtual ~Application();
	
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }

		void Run();

		void Close();

		static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;

	};

	// To be defined in client
	Application* CreateApplication();

}



