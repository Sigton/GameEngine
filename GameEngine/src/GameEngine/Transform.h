#pragma once

#include <glm/glm.hpp>

namespace GameEngine {

	class Transform
	{
	public:
		Transform();
		Transform(const glm::vec3& position);
		Transform(const glm::vec3& position, const glm::vec3& rotation);
		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
		Transform(const Transform& transform);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetRotation() const { return m_Rotation; }
		inline const glm::vec3& GetScale() const { return m_Scale; }

		inline void SetPosition(glm::vec3& position) { m_Position = position; }
		inline void SetRotation(glm::vec3& rotation) { m_Rotation = rotation; }
		inline void SetScale(glm::vec3& scale) { m_Scale = scale; }

		inline const glm::mat4& GetLocalToWorldMatrix() { RecalculateMatrix(); return m_Matrix; }
		inline const glm::mat4& GetWorldToLocalMatrix() { RecalculateMatrix(); return glm::inverse(m_Matrix); }

		const glm::vec3& GetForward() const;
		const glm::vec3& GetRight() const;
		const glm::vec3& GetUp() const;

	private:
		void RecalculateMatrix();

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		glm::mat4 m_Matrix;
	};

}
