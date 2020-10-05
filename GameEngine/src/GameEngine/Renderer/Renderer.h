#pragma once

#include "GameEngine/Core.h"

#include "GameEngine/Renderer/GraphicsContext.h"
#include "GameEngine/Renderer/RenderCommand.h"
#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Texture.h"

#include "GameEngine/Renderer/PerspectiveCamera.h"

#include "GameEngine/Transform.h"

namespace GameEngine {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(PerspectiveCamera& perspectiveCamera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Transform>& transform);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> s_SceneData;
	};

}
