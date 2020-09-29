#include <GameEngine.h>
#include <GameEngine/EntryPoint.h>

#include <imgui/imgui.h>

class GameLayer : public GameEngine::Layer
{
public:
	GameLayer()
		: Layer("Game Layer")
	{
	}

	virtual void OnAttach() override
	{

	}

	virtual void OnUpdate() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Demo window");
		ImGui::Button("Hello!");
		ImGui::End();
	}
};


class SandboxApp : public GameEngine::Application
{
public:
	SandboxApp()
	{
		PushLayer(new GameLayer());
	}
};


GameEngine::Application* GameEngine::CreateApplication()
{
	return new SandboxApp();
}
