#pragma once

#include <glm/glm.hpp>

#include "SGUI/Core/KeyCodes.h"
#include "SGUI/Core/MouseCodes.h"

namespace SGUI {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
