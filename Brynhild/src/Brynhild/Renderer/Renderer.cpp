#include "PreCompiledHeader.h"
#include "Renderer.h"

namespace Brynhild {
  Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

  void Renderer::BeginPlay(Camera& camera)
  {
    s_SceneData->ProjectionView = camera.GetProjectionViewMatrix();
  }

  void Renderer::EndPlay()
  {
  }

  void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
  {
    shader->Bind();
    //shader->SetMat4("u_ProjectionView", s_SceneData->ProjectionView);
    
    vertexArray->Bind();
    RenderManager::DrawElements(vertexArray);
  }
}
