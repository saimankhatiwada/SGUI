#include <SGUI.h>
#include <SGUI/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace SGUI {

	class SGUInut : public Application
	{
	public:
		SGUInut()
			: Application("Synthesia-Editor")
		{
			PushLayer(new EditorLayer());
		}

		~SGUInut()
		{
		}
	};

	Application* CreateApplication()
	{
		return new SGUInut();
	}

}
