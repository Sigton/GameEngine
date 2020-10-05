#pragma once

#include "GameEngine/Core.h"

#include "GameEngine/Renderer/GraphicsContext.h"
#include "GameEngine/Renderer/RenderCommand.h"
#include "GameEngine/Renderer/Shader.h"

namespace GameEngine {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}
