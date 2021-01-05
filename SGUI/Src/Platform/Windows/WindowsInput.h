#pragma once

#include "SGUI/Input.h"

namespace SGUI
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int KeyCode) override;
		virtual bool IsMouseButtonPressedImpl(int Button) override;
		virtual float IsGetMouseXImpl() override;
		virtual float IsGetMouseYImpl() override;
		virtual std::pair<float,float> IsGetMousePositionImpl() override;
	};
}