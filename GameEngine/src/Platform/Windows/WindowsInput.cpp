#include "gepch.h"
#include "GameEngine/Input.h"

#include "GameEngine/Application.h"
#include <GLFW/glfw3.h>

namespace GameEngine {

	void Input::Init()
	{
		s_OldMousePosition = GetMousePosition();
	}

	void Input::OnUpdate()
	{
		s_OldMousePosition = GetMousePosition();
	}

	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return glm::vec2((float)xpos, (float)ypos);
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

	glm::vec2 Input::GetMouseDelta()
	{
		return GetMousePosition() - s_OldMousePosition;
	}

	float Input::GetMouseDeltaX()
	{
		return GetMouseDelta().x;
	}

	float Input::GetMouseDeltaY()
	{
		return GetMouseDelta().y;
	}

}
