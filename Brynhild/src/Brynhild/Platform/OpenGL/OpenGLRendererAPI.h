#pragma once
#include "Brynhild/Renderer/RendererAPI.h"

namespace Brynhild {
  class OpenGLRendererAPI : public RendererAPI {
    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) override;

    void OpenGLRendererAPI::DrawElements(const std::shared_ptr<VertexArray>& vertexArray) override;
  };
}
