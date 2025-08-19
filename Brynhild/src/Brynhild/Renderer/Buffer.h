#pragma once

namespace Brynhild {
  struct ShaderType {

  };

  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() {};

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    
    static VertexBuffer* Create(float* vertices, uint32_t size);
  };

  class VertexArray
  {
  public:
    virtual ~VertexArray() {};

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static VertexArray* Create(float* vertices, uint32_t size);
  };

  class ElementBuffer
  {
  public:
    virtual ~ElementBuffer() {};

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual uint32_t GetCount() = 0; //Get count of how many indices there are

    static ElementBuffer* Create(uint32_t* indices, uint32_t size);
  };

}

