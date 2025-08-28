#include "PreCompiledHeader.h"
#include "Renderer.h"

namespace Brynhild {
  void Renderer::BeginPlay()
  {
  }
  void Renderer::EndPlay()
  {
  }
  void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
  {
    shader->Bind();
    vertexArray->Bind();
    RenderManager::DrawElements(vertexArray);
  }
}
