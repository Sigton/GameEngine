#include <GameEngine.h>
#include <GameEngine/EntryPoint.h>


class SandboxApp : public GameEngine::Application
{
public:
	SandboxApp()
	{
		GE_TRACE("Example of client logger working");
	}
};


GameEngine::Application* GameEngine::CreateApplication()
{
	return new SandboxApp();
}
