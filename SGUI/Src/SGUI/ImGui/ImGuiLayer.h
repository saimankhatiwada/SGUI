#pragma once
#include "SGPCH.h"
#include "SGUI/Layer.h"
#include "SGUI/Events/KeyEvent.h"
#include "SGUI/Events/MouseEvent.h"
#include "SGUI/Events/ApplicationEvent.h"

namespace SGUI
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}