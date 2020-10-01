#pragma once

#include "GameEngine/Core.h"

#include "GameEngine/Renderer/GraphicsContext.h"
#include "GameEngine/Renderer/RendererAPI.h"
#include "GameEngine/Renderer/Buffer.h"

namespace GameEngine {

	class Renderer
	{
	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}
