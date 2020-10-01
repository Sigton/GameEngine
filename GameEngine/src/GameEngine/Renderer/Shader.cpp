#include "gepch.h"
#include "GameEngine/Renderer/Shader.h"

#include "GameEngine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace GameEngine {

	std::shared_ptr<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		GE_CORE_ASSERT(false, "RendererAPI::None is not currently supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
		}
	}

}