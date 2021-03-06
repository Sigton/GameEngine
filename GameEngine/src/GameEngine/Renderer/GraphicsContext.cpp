#include "gepch.h"
#include "GameEngine/Renderer/GraphicsContext.h"

#include "GameEngine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace GameEngine {

	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		GE_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
