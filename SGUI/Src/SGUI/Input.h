#pragma once

#include "SGUI/Core.h"

namespace SGUI
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int Button) { return s_Instance->IsMouseButtonPressedImpl(Button); }
		inline static float GetMouseX() { return s_Instance->IsGetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->IsGetMouseYImpl(); }
		inline static std::pair<float,float> GetMousePosition() { return s_Instance->IsGetMousePositionImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int KeyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int Button) = 0;
		virtual float IsGetMouseXImpl() = 0;
		virtual float IsGetMouseYImpl() = 0;
		virtual std::pair<float,float> IsGetMousePositionImpl() = 0;
	private:
		static Input* s_Instance;
	};
}