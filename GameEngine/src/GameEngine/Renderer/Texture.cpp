#include "gepch.h"
#include "GameEngine/Renderer/Texture.h"

#include "GameEngine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace GameEngine {

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		GE_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(path);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}