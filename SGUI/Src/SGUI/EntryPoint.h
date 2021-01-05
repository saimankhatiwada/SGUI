#pragma once

#ifdef SG_PLATFORM_WINDOW

extern SGUI::Application* SGUI::CreateApplication();

int main(int argc, char** argv)
{
	SGUI::Log::Init();
	SG_PROFILE_BEGIN_SESSION("Startup", "Performance/SGUIProfile-startup.json");
	auto app = SGUI::CreateApplication();
	SG_PROFILE_END_SESSION();

	SG_PROFILE_BEGIN_SESSION("Runtime", "Performance/SGUIProfile-runtime.json");
	app->Run();
	SG_PROFILE_END_SESSION();

	SG_PROFILE_BEGIN_SESSION("EndUp", "Performance/SGUIProfile-endup.json");
	delete app;
	SG_PROFILE_END_SESSION();
}
#endif 