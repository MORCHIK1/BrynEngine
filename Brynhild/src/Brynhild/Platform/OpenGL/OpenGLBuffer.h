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

    void SetLayout(BufferLayoutList list) override;
    const BufferLayoutList& GetLayout() const override;

  private:
    BufferLayoutList m_LayoutList;
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
    OGLVertexArray();
    ~OGLVertexArray();

    void Bind() override;
    void Unbind() override;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuf) override;
    void AddElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuf) override;

    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() override;
    const std::shared_ptr<ElementBuffer>& GetElementBuffer() override;

  private:
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBufList;
    std::shared_ptr<ElementBuffer> m_ElementBuf;
    uint32_t m_ArrayID;
    uint32_t m_AttribArray = 0;
  };

  class OGLUniformBuffer : public UniformBuffer
  {
  public:
    OGLUniformBuffer(const std::vector<char>& constantBufferData, uint32_t layerIndex);
    ~OGLUniformBuffer();

    void Bind() override;
    void Unbind() override;

    void UpdateUBO(const std::vector<char>& constantBufferData) override;

  private:
    uint32_t m_Layout;
    uint32_t m_UniformID;
  };
}
 