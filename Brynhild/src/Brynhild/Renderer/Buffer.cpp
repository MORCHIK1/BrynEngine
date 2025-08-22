#include "PreCompiledHeader.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Brynhild/Platform/OpenGL/OpenGLBuffer.h"

namespace Brynhild {
  std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
  {
    switch (Renderer::GetRendererAPI()) 
    {
    case RendererAPI::None:
      BRYN_CORE_ERROR("Render API None is not supported!");
      return nullptr;
    case RendererAPI::OpenGL:
      return std::make_shared<OGLVertexBuffer>(vertices, size);
    }

    BRYN_CORE_ASSERT(false, "Wrong RendererAPI for VertexBuffer!");
    return nullptr;
  }

  void BufferLayoutList::CalculateStrideAndOffset() {
    m_Stride = 0;
    uint32_t previousOffset = 0;

    for (BufferLayoutElement el : m_LayoutElements) {
      m_Stride += ShaderDataTypeSize(el.DataType);
      el.Offset = previousOffset;
      previousOffset += ShaderDataTypeSize(el.DataType);
    }
    BRYN_CORE_INFO("STRIDE: {0}", m_Stride);
  }

  
  std::shared_ptr <ElementBuffer> ElementBuffer::Create(uint32_t* indices, uint32_t size)
  {
    switch (Renderer::GetRendererAPI())
    {
    case RendererAPI::None:
      BRYN_CORE_ERROR("Render API None is not supported!");
      return nullptr;
    case RendererAPI::OpenGL:
      return std::make_shared<OGLElementBuffer>(indices, size);
    }

    BRYN_CORE_ASSERT(false, "Wrong RendererAPI for ElementBuffer!");
    return nullptr;
  }
  
  VertexArray* VertexArray::Create()
  {
    switch (Renderer::GetRendererAPI())
    {
    case RendererAPI::None:
      BRYN_CORE_ERROR("Render API None is not supported!");
      return nullptr;
    case RendererAPI::OpenGL:
      return new OGLVertexArray();
    }

    BRYN_CORE_ASSERT(false, "Wrong RendererAPI for VertexArray!");
    return nullptr;
  }

}

