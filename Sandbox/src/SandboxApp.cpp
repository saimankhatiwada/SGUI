#include <SGUI.h>
#include <SGUI/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public SGUI::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

SGUI::Application* SGUI::CreateApplication()
{
	return new Sandbox();
}
