#pragma once

#include <glm/glm.hpp>

namespace GameEngine {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov = 60.0f, float aspect = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 50.0f);

		void SetProjection(float fov, float aspect, float nearPlane, float farPlane);

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const {	return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalculateViewMatrix(); }

		inline const glm::vec3& GetRotation() const { return m_Rotation; }
		inline void SetRotation(const glm::vec3& rot) { m_Rotation = rot; RecalculateViewMatrix(); }

	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

	};

}
