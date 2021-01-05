#pragma once

#include "RenderComand.h"
#include "Platform/OpenGl/OpenGlRendererAPI.h"

namespace SGUI
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGlRendererAPI;
}