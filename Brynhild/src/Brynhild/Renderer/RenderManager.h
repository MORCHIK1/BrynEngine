#pragma once

#include <glm/glm.hpp>
#include "RendererAPI.h"

namespace Brynhild {

  class RenderManager {
public:
  static void SetClearColor(const glm::vec4& color);
  
  static void DrawElements(const std::shared_ptr<VertexArray>& vertexArray);

private:
    static RendererAPI* s_API;
  };

}
