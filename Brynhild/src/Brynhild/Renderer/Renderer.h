#pragma once

#include "Brynhild/Renderer/Buffer.h"
#include "Brynhild/Renderer/Shader.h"
#include "RenderManager.h"

namespace Brynhild {

  
  class Renderer
  {
  public:
    inline static RendererAPI::API GetRendererAPI() { return RendererAPI::GetAPI(); }

    static void BeginPlay();
    static void EndPlay();

    static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);
  private:
  };

}

