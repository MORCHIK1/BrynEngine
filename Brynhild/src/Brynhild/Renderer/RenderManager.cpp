#include "PreCompiledHeader.h"
#include "RenderManager.h"

#include "Brynhild/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Brynhild {
  RendererAPI* RenderManager::s_API = new OpenGLRendererAPI;

  void RenderManager::SetClearColor(const glm::vec4& color)
  {
    s_API->SetClearColor(color);
  }
  void RenderManager::DrawElements(const std::shared_ptr<VertexArray>& vertexArray)
  {
    s_API->DrawElements(vertexArray);
  }
}

