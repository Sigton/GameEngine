#include "gepch.h"
#include "GameEngine/Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace GameEngine {

	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
	#ifdef GE_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(props);
	#else
		GE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}