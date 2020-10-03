#pragma once

#include "GameEngine/Core.h"

#include <string>
#include <glm/glm.hpp>

namespace GameEngine {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// functions for uploading uniforms
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;


		static std::shared_ptr<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
	};

}
