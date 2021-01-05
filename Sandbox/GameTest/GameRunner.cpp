#include "SGUI.h"
#include "SGUI/EntryPoint.h"
#include "GameLayer.h"

class Sandbox : public SGUI::Application
{
public:
	Sandbox()
	{
		PushLayer(new GameLayer());
	}
	~Sandbox()
	{

	}
};

SGUI::Application* SGUI::CreateApplication()
{
	return new Sandbox();
}