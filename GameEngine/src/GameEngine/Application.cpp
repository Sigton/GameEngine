#include "gepch.h"
#include "GameEngine/Application.h"

#include "GameEngine/Core.h"

#include "GameEngine/Log.h"

#include <glad/glad.h>


namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(GE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// define geometry and indices
		float vertices[3 * 3] = {
			-0.5f,	-0.5f,	 0.0f,
			 0.5f,	-0.5f,	 0.0f,
			 0.0f,	 0.5f,	 0.0f
		};

		unsigned int indices[3] = {
			0, 1, 2
		};

		// gen vertex array
		m_VertexArray = VertexArray::Create();

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices)/sizeof(unsigned int));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
}
)";

		std::string fragmentSource = R"(
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(0.8, 0.2, 0.2, 1.0);
}
)";
		m_Shader = Shader::Create(vertexSource, fragmentSource);
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(Application::OnWindowResize));

		// let each layer process the event until the event gets marked as handled
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
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

			// CLEAR FROM LAST FRAME
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// SUBMIT TO RENDERER
			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			// UPDATE LAYERS

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			

			m_Window->OnUpdate();
		}
	}

}

