#pragma once

#include "RenderManager.h"

#include "Brynhild/Renderer/Camera.h"
#include "Brynhild/Renderer/Buffer.h"
#include "Brynhild/Renderer/Shader.h"

namespace Brynhild {

  
  class Renderer
  {
  public:
    inline static RendererAPI::API GetRendererAPI() { return RendererAPI::GetAPI(); }

    static void BeginPlay(Camera& camera);
    static void EndPlay();

    static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);
  private:
    struct SceneData
    {
      glm::mat4 ProjectionView;
    };

    static SceneData* s_SceneData;
  };

}

