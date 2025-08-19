#include "PreCompiledHeader.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Brynhild/Platform/OpenGL/OpenGLBuffer.h"

namespace Brynhild {
  VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
  {
    switch (Renderer::GetRendererAPI()) 
    {
    case RendererAPI::None:
      BRYN_CORE_ERROR("Render API None is not supported!");
      return nullptr;
    case RendererAPI::OpenGL:
      return new OGLVertexBuffer(vertices, size);
    }

    BRYN_CORE_ASSERT(false, "Wrong RendererAPI!");
    return nullptr;
  }
  
  
  ElementBuffer* ElementBuffer::Create(uint32_t* indices, uint32_t size)
  {
    switch (Renderer::GetRendererAPI())
    {
    case RendererAPI::None:
      BRYN_CORE_ERROR("Render API None is not supported!");
      return nullptr;
    case RendererAPI::OpenGL:
      return new OGLElementBuffer(indices, size);
    }

    BRYN_CORE_ASSERT(false, "Wrong RendererAPI!");
    return nullptr;
  }
  
}

