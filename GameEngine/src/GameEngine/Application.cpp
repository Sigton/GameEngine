#include "gepch.h"
#include "GameEngine/Application.h"

#include "GameEngine/Core.h"

#include "GameEngine/Log.h"


namespace GameEngine {

	Application::Application()
	{
		GE_CORE_TRACE("Application has opened");
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (true);
	}

}

