#include "gepch.h"
#include "GameEngine/Renderer/VertexArray.h"

#include "GameEngine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GameEngine {

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		GE_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLVertexArray>();
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
