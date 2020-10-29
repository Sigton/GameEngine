#include "gepch.h"
#include "GameEngine/Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace GameEngine {

	Transform::Transform()
		: m_Position(glm::vec3(0)), m_Rotation(glm::vec3(0)), m_Scale(glm::vec3(1))
	{
		RecalculateMatrix();
	}

	Transform::Transform(const glm::vec3& position)
		: m_Position(position), m_Rotation(glm::vec3(0)), m_Scale(glm::vec3(1))
	{
		RecalculateMatrix();
	}

	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation)
		: m_Position(position), m_Rotation(rotation), m_Scale(glm::vec3(1))
	{
		RecalculateMatrix();
	}

	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
		RecalculateMatrix();
	}

	Transform::Transform(const Transform& transform)
		: m_Position(transform.GetPosition()), m_Rotation(transform.GetRotation()), m_Scale(transform.GetScale())
	{
		RecalculateMatrix();
	}

	void Transform::RecalculateMatrix()
	{
		glm::mat4 pos = glm::translate(glm::mat4(1), m_Position);
		glm::mat4 rot = glm::orientate4(glm::vec3(m_Rotation.x, m_Rotation.z, m_Rotation.y));
		glm::mat4 scale = glm::scale(glm::mat4(1), m_Scale);

		m_Matrix = pos * rot * scale;
	}

	const glm::vec3& Transform::GetForward() const
	{
		return glm::vec3(glm::orientate4(glm::vec3(m_Rotation.x, m_Rotation.z, m_Rotation.y)) * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	}

	const glm::vec3& Transform::GetRight() const
	{
		return glm::vec3(glm::orientate4(glm::vec3(m_Rotation.x, m_Rotation.z, m_Rotation.y)) * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	}

	const glm::vec3& Transform::GetUp() const
	{
		return glm::vec3(glm::orientate4(glm::vec3(m_Rotation.x, m_Rotation.z, m_Rotation.y)) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	}

}
