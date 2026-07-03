#include "PreCompiledHeader.h"
#include "Shader.h"

#include "Brynhild/Renderer/Renderer.h"
#include "Brynhild/Platform/OpenGL/OpenGLShader.h"

namespace Brynhild {

  std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
  {
    switch (Renderer::GetRendererAPI()) {
    case RendererAPI::API::None:
      BRYN_CORE_ERROR("No shader for API None!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLShader>(filepath);
    }

    BRYN_CORE_ASSERT(false, "Unknown RendererAPI for Shader!");
    return nullptr;
  }
}