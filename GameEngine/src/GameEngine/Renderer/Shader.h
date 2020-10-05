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
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;


		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static std::shared_ptr<Shader> Create(const std::string& path);
	};

}
