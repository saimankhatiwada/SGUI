#pragma once

#include "SGUI/Core/Layer.h"

#include "SGUI/Events/ApplicationEvent.h"
#include "SGUI/Events/KeyEvent.h"
#include "SGUI/Events/MouseEvent.h"

namespace SGUI {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		
		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}
