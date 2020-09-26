#pragma once

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv)
{

	auto app = GameEngine::CreateApplication();

	app->Run();

	delete app;

	return 0;
}
