#include "SGUI.h"
#include "SGUI/EntryPoint.h"
#include "EditorLayer.h"

namespace SGUI
{
	class SynthesiaEditor : public Application
	{
	public:
		SynthesiaEditor()
		{
			PushLayer(new EditorLayer());
		}
		~SynthesiaEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new SynthesiaEditor();
	}
}