#include "PreCompiledHeader.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Brynhild {
  void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
  {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  
  void OpenGLRendererAPI::DrawElements(const std::shared_ptr<VertexArray>& vertexArray)
  {
    glDrawElements(GL_TRIANGLES, vertexArray->GetElementBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
  }
}

