#pragma once

#include "SGUI/Events/Event.h"
#include "Time/TimeSteps.h"

namespace SGUI
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeSteps ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImguiRender() {}

		inline const std::string GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}


