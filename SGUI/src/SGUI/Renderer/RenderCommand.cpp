#include "hzpch.h"
#include "SGUI/Renderer/RenderCommand.h"

namespace SGUI {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
