#include "gepch.h"
#include "GameEngine/Renderer/Renderer.h"

namespace GameEngine {

	void Renderer::Init()
	{

	}

	void Renderer::Shutdown()
	{

	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

}