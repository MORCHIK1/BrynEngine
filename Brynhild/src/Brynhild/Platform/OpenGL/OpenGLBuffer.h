#pragma once

#include "Brynhild/Renderer/Buffer.h"

namespace Brynhild {
  class OGLVertexBuffer : public VertexBuffer
  {
  public:
    OGLVertexBuffer(float* vertices, uint32_t size);
    ~OGLVertexBuffer();

    void Bind() override;
    void Unbind() override;
    
  private:
    uint32_t m_VertexID;
  };

  class OGLElementBuffer : public ElementBuffer
  {
  public:
    OGLElementBuffer(uint32_t* indices, uint32_t count);
    ~OGLElementBuffer();

    void Bind() override;
    void Unbind() override;

    inline uint32_t GetCount() override { return m_Count; };

  private:
    uint32_t m_ElementID;
    uint32_t m_Count;
  };

  class OGLVertexArray : public VertexArray
  {
  public:
    OGLVertexArray(BufferLayoutList vertices);
    ~OGLVertexArray();

    void Bind() override;
    void Unbind() override;

    void SetLayout(BufferLayoutList list) override;
    void EnableVertexAttrib() override;

  private:
    uint32_t m_ArrayID;
    uint32_t m_AttribArray = 0;
    BufferLayoutList m_LayoutList;
  };
}
 