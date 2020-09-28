#pragma once

#include "GameEngine/Log.h"

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv)
{

	GameEngine::Log::Init();


	auto app = GameEngine::CreateApplication();

	app->Run();

	delete app;


	return 0;
}
