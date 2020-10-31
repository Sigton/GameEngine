#pragma once

#include <glm/glm.hpp>

#include "GameEngine/KeyCodes.h"
#include "GameEngine/MouseCodes.h"

namespace GameEngine {

	class Input
	{
	public:
		static void Init();
		static void OnUpdate();

		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		static glm::vec2 GetMouseDelta();
		static float GetMouseDeltaX();
		static float GetMouseDeltaY();
	private:
		static glm::vec2 s_OldMousePosition;
	};

}
