#include "gepch.h"
#include "GameEngine/Renderer/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace GameEngine {

	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float nearPlane, float farPlane)
		: m_Position(glm::vec3(0)), m_Rotation(glm::vec3(0))
	{
		m_ProjectionMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetProjection(float fov, float aspect, float nearPlane, float farPlane)
	{
		m_ProjectionMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1), m_Position) * glm::orientate4(glm::vec3(m_Rotation.x, m_Rotation.z, m_Rotation.y));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}