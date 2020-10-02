#include "gepch.h"
#include "GameEngine/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GameEngine {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
