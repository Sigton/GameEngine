#include <GameEngine.h>
#include <GameEngine/EntryPoint.h>


class SandboxApp : public GameEngine::Application
{
public:
	SandboxApp()
	{

	}
};


GameEngine::Application* GameEngine::CreateApplication()
{
	return new SandboxApp();
}
