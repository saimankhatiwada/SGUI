#pragma once
#include "SGUI/Core/Base.h"

#ifdef SG_PLATFORM_WINDOWS

extern SGUI::Application* SGUI::CreateApplication();

int main(int argc, char** argv)
{
	SGUI::Log::Init();

	SG_PROFILE_BEGIN_SESSION("Startup", "SGUIProfile-Startup.json");
	auto app = SGUI::CreateApplication();
	SG_PROFILE_END_SESSION();

	SG_PROFILE_BEGIN_SESSION("Runtime", "SGUIProfile-Runtime.json");
	app->Run();
	SG_PROFILE_END_SESSION();

	SG_PROFILE_BEGIN_SESSION("Shutdown", "SGUIProfile-Shutdown.json");
	delete app;
	SG_PROFILE_END_SESSION();
}

#endif
